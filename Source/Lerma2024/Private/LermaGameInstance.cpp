// Fill out your copyright notice in the Description page of Project Settings.

#include "LermaGameInstance.h"
#include "iostream"
#include "windows.h"
#include <locale>
#include <codecvt>
#include <string>
#include <tlhelp32.h>
#include <JsonObjectConverter.h>

ULermaGameInstance::ULermaGameInstance()
{
}

void ULermaGameInstance::BeginUpdate()
{
}

void ULermaGameInstance::GetInfraestructura(FString jsonInfra)
{
	TSharedPtr<FJsonObject> rspObjAsJson;
	FInfraestructura JsonData;
	FJsonObjectConverter::JsonObjectStringToUStruct<FInfraestructura>(jsonInfra, &JsonData, 0, 0);
	this->Infraestructura = JsonData;
	if (this->onInfraestructuraCompleted.IsBound()) this->onInfraestructuraCompleted.Broadcast();
}

void ULermaGameInstance::GetUpdate(FString jsonUpdate)
{
	TSharedPtr<FJsonObject> RspObjAsJson;
	FUpdateUnrealSites JsonData;
	FJsonObjectConverter::JsonObjectStringToUStruct<FUpdateUnrealSites>(jsonUpdate, &JsonData, 0, 0);
	this->UpdatedData = JsonData;
	if (this->onUpdateCompleted.IsBound())
		this->onUpdateCompleted.Broadcast();
}

void ULermaGameInstance::FirstServerRequest(FString URL)
{
	this->proccessedDataRequest = FHttpModule::Get().CreateRequest();
	this->proccessedDataRequest->OnProcessRequestComplete().BindUObject(this, &ULermaGameInstance::OnResponseProcessedTableReiceved);
	this->proccessedDataRequest->SetURL(URL);
	this->proccessedDataRequest->SetVerb("Get");
	this->proccessedDataRequest->ProcessRequest();
}

void ULermaGameInstance::RefreshFromServer(FString URL)
{
	this->proccessedDataRequest = FHttpModule::Get().CreateRequest();
	this->proccessedDataRequest->OnProcessRequestComplete().BindUObject(this, &ULermaGameInstance::OnResponseProcessedUpdate);
	this->proccessedDataRequest->SetURL(URL);
	this->proccessedDataRequest->SetVerb("Get");
	this->proccessedDataRequest->ProcessRequest();
}

void ULermaGameInstance::ExecuteExternal(FString path)
{
	path = path.Replace(TEXT("/"), TEXT("\\"), ESearchCase::CaseSensitive);
	std::string s = std::string(TCHAR_TO_UTF8(*path));
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::wstring wide = converter.from_bytes(s);
	ShellExecute(NULL, L"open", wide.c_str(), NULL, NULL, SW_SHOWMAXIMIZED);
}

FString ULermaGameInstance::GetCurrentPath()
{
	FString RelativePath = FPaths::ProjectDir();
	FString FullPath = IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead(*RelativePath);
	return FullPath;
}

FCommandResponse ULermaGameInstance::SendCommand(FString URL, FCommandVWC command)
{
	this->proccessedDataRequest = FHttpModule::Get().CreateRequest();

	this->proccessedDataRequest->OnProcessRequestComplete().BindUObject(this, &ULermaGameInstance::OnCommandResponseReceived);

	this->proccessedDataRequest->SetURL(URL);

	this->proccessedDataRequest->SetVerb("Post");
	this->proccessedDataRequest->SetHeader("Content-Type", "application/json");

	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

	JsonObject->SetStringField("IdEstacion", FString::FromInt(command.IdEstacion));
	JsonObject->SetStringField("RegModbus", FString::FromInt(command.RegModbus));
	JsonObject->SetStringField("Codigo", FString::FromInt(command.Codigo));
	JsonObject->SetStringField("Usuario", command.Usuario);

	FString OutputString;
	TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

	this->proccessedDataRequest->SetContentAsString(OutputString);
	this->proccessedDataRequest->ProcessRequest();

	return FCommandResponse();
}

int ULermaGameInstance::ArmarCodigo(int Estacion, int numeroBomba, int acctionBomba)
{
	return Estacion << 8 | numeroBomba << 4 | acctionBomba;
}

void ULermaGameInstance::OnResponseProcessedTableReiceved(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	if (Response == nullptr || Response->GetResponseCode() != 200 || !bConnectedSuccessfully) {
		if (this->onInfraestructuraFailed.IsBound()) this->onInfraestructuraFailed.Broadcast();
		return;
	}

	TSharedPtr<FJsonObject> rspObjAsJson;
	FString ResponseBody = Response->GetContentAsString();
	FInfraestructura JsonData;
	FJsonObjectConverter::JsonObjectStringToUStruct<FInfraestructura>(ResponseBody, &JsonData, 0, 0);

	this->Infraestructura = JsonData;

	if (this->onInfraestructuraCompleted.IsBound()) this->onInfraestructuraCompleted.Broadcast();
}

void ULermaGameInstance::OnResponseProcessedUpdate(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	if (Response == nullptr || Response->GetResponseCode() != 200 || !bConnectedSuccessfully)
	{
		if (this->onUpdateFailed.IsBound())
			this->onUpdateFailed.Broadcast();

		return;
	}

	TSharedPtr<FJsonObject> RspObjAsJson;
	FString RspBody = Response->GetContentAsString();

	FUpdateUnrealSites JsonData;
	FJsonObjectConverter::JsonObjectStringToUStruct<FUpdateUnrealSites>(RspBody, &JsonData, 0, 0);


	this->UpdatedData = JsonData;

	if (this->onUpdateCompleted.IsBound())
		this->onUpdateCompleted.Broadcast();
}

void ULermaGameInstance::OnCommandResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	if (Response == nullptr || Response->GetResponseCode() != 200 || !bConnectedSuccessfully)
	{
		if (this->onCommandFailed.IsBound())
			this->onCommandFailed.Broadcast();

		return;
	}

	TSharedPtr<FJsonObject> RspObjAsJson;
	FString RspBody = Response->GetContentAsString();

	FCommandResponse JsonData;
	FJsonObjectConverter::JsonObjectStringToUStruct<FCommandResponse>(RspBody, &JsonData, 0, 0);

	this->CommmandResponse = JsonData;

	if (this->onCommandCompleted.IsBound()) {
		this->onCommandCompleted.Broadcast();
	}
}

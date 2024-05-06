// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Http.h"
#include "LermaGameInstance.generated.h"

UENUM(BlueprintType)
enum class TipoSignal : uint8 {
	DEFAULT = 0,
	NIVEL = 1,
	PRESION = 2,
	GASTO = 3,
	TOTALIZADO = 4,
	VALVULAANALOGICA = 5,
	VALVULADISCRETA = 6,
	BOMBA = 7,
	PERILLABOMBA = 8,
	PERILLAGENERAL = 9,
	VOLTAJE = 10,
	ENLACE = 11,
	FALLAC = 12,
	TIEMPO = 13,
	MANTENIMIENTO = 14,
	PUERTAABIERTA = 15
};


USTRUCT(BlueprintType)
struct FSemaforo
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite) float Normal = 0;
	UPROPERTY(BlueprintReadWrite) float Preventivo = 0;
	UPROPERTY(BlueprintReadWrite) float Critico = 0;
	UPROPERTY(BlueprintReadWrite) float Altura = 0; //No llega la altura
};

USTRUCT(BlueprintType)
struct FSignalBase
{
	GENERATED_USTRUCT_BODY()
public:
	// Falta la fecha
	UPROPERTY(BlueprintReadWrite) int IdSignal = 0;
	UPROPERTY(BlueprintReadWrite) float Valor = 0;
	UPROPERTY(BlueprintReadWrite) int DentroRango = 0; //Llega como entero
	UPROPERTY(BlueprintReadWrite) int IndiceImagen = 0;
};

USTRUCT(BlueprintType)
struct FSignalDescription : public FSignalBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite) TipoSignal IdTipoSignal;
	UPROPERTY(BlueprintReadWrite, meta = (DisplayName="Nombre")) FString NombreSignal; //NombreSignal
	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "Ordinal")) int OrdinalSignal = 0; //OrdinalSignal
	UPROPERTY(BlueprintReadWrite) FSemaforo Semaforo;
	UPROPERTY(BlueprintReadWrite) int Linea = 0; //No viene
};

USTRUCT(BlueprintType)
struct FSignalsDescriptionContainer {
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite) TipoSignal TipoSignal;
	UPROPERTY(BlueprintReadWrite) TArray<FSignalDescription> SignalsDescription;
};

USTRUCT(BlueprintType)
struct FSignalsContainer {
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite) TipoSignal TipoSignal;
	UPROPERTY(BlueprintReadWrite) TArray<FSignalBase> Signals;
};

USTRUCT(BlueprintType)
struct FSiteBase {
	GENERATED_USTRUCT_BODY()
public:
	// Falta voltaje y IdWeb
	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "Id")) int IdSitio = 0; //IdSitio
	UPROPERTY(BlueprintReadWrite) bool Enlace = 0; //Llega Boleano
	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "Tiempo")) FDateTime Fecha; //Fecha
	UPROPERTY(BlueprintReadWrite) bool FallaAC = false; //No viene del servicio
	UPROPERTY(BlueprintReadWrite) TArray<FSignalsContainer> SignalsContainer;
};


USTRUCT(BlueprintType)
struct FSiteDescription : public FSiteBase {
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite) FString Nombre;
	UPROPERTY(BlueprintReadWrite) FString Abreviacion;
	UPROPERTY(BlueprintReadWrite) float Latitud = 0;
	UPROPERTY(BlueprintReadWrite) float Longitud = 0;
	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "Grupo")) int Estructura = 0; //Estructura
	UPROPERTY(BlueprintReadWrite, meta = (DisplayName = "TipoEstacion")) int TipoLumbrera = 0; //TipoLumbrera
	UPROPERTY(BlueprintReadWrite) FString NombreCompleto;
	UPROPERTY(BlueprintReadWrite) FString NombreCorto;
	UPROPERTY(BlueprintReadWrite) TArray <FSignalsDescriptionContainer> SignalsDescriptionContainer;
};

USTRUCT(BlueprintType)
struct FInfraestructura {
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite) TArray<FSiteDescription> Sites;
};

USTRUCT(BlueprintType)
struct FUpdateUnrealSites {
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite) int Version = 0;
	UPROPERTY(BlueprintReadWrite) TArray<FSiteBase> Sites;
};

USTRUCT(BlueprintType)
struct FCommandVWC
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite)int IdEstacion;
	UPROPERTY(BlueprintReadWrite)int Codigo;
	UPROPERTY(BlueprintReadWrite)FString Usuario;
	UPROPERTY(BlueprintReadWrite)int RegModbus;
};

USTRUCT(BlueprintType)
struct FCommandResponse
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadWrite)bool ResponseBln;
	UPROPERTY(BlueprintReadWrite)FString ResponseText;
};

/**
 *
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGIUpdateFromServerCompleted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGIUpdateFromServerFailed);

UCLASS(Blueprintable)
class LERMA2024_API ULermaGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite) FInfraestructura Infraestructura;
	UPROPERTY(BlueprintReadWrite) FUpdateUnrealSites UpdatedData;

	UPROPERTY(BlueprintReadWrite) FCommandResponse CommmandResponse;

	UPROPERTY(BlueprintAssignable, Category = "Socket|Event") FOnGIUpdateFromServerCompleted onInfraestructuraCompleted;

	UPROPERTY(BlueprintAssignable, Category = "Socket|Event") FOnGIUpdateFromServerFailed onInfraestructuraFailed;

	UPROPERTY(BlueprintAssignable, Category = "Socket|Event") FOnGIUpdateFromServerCompleted onUpdateCompleted;

	UPROPERTY(BlueprintAssignable, Category = "Socket|Event") FOnGIUpdateFromServerFailed onUpdateFailed;

	UPROPERTY(BlueprintAssignable, Category = "Socket|Event") FOnGIUpdateFromServerCompleted onCommandCompleted;

	UPROPERTY(BlueprintAssignable, Category = "Socket|Event") FOnGIUpdateFromServerFailed onCommandFailed;

private:
	FHttpRequestPtr proccessedDataRequest;
public:

	ULermaGameInstance();

	UFUNCTION(BlueprintCallable) void BeginUpdate();

	UFUNCTION(BlueprintCallable) void GetInfraestructura(FString jsonInfra);
	UFUNCTION(BlueprintCallable) void GetUpdate(FString jsonUpdate);

	UFUNCTION(BlueprintCallable) void FirstServerRequest(FString URL);

	UFUNCTION(BlueprintCallable) void RefreshFromServer(FString URL);

	UFUNCTION(BlueprintCallable) void ExecuteExternal(FString path);

	UFUNCTION(BlueprintCallable) FString GetCurrentPath();

	UFUNCTION(BlueprintCallable) FCommandResponse SendCommand(FString URL, FCommandVWC command);

	UFUNCTION(BlueprintCallable) int ArmarCodigo(int Estacion, int numeroBomba, int acctionBomba);

private:
	void OnResponseProcessedTableReiceved(FHttpRequestPtr  Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);
	void OnResponseProcessedUpdate(FHttpRequestPtr  Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);
	void OnCommandResponseReceived(FHttpRequestPtr  Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);
};

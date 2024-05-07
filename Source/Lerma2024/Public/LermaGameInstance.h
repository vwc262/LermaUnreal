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

UENUM(BlueprintType)
enum class Sitios : uint8 {
	DEFAULT = 0,
	S24A = 1,
	S26A = 2,
	S27A = 3,
	S28A = 4,
	S31A = 5,
	S32A = 6,
	S33A = 7,
	S34A = 8,
	S35A = 9,
	S36A = 10,
	S37A = 11,
	S38A = 12,
	S40A = 13,
	S47A = 14,
	S50A = 15,
	S54A = 16,
	S57A = 17,
	S58A = 18,
	S59A = 19,
	S60A = 20,
	S63A = 21,
	S69A = 22,
	S70A = 23,
	S71A = 24,
	S74A = 25,
	S75A = 26,
	N1 = 27,
	N1B = 28,
	N2 = 29,
	N3 = 30,
	N4 = 31,
	N5 = 32,
	N6 = 33,
	N7 = 34,
	N8 = 35,
	N9 = 36,
	N9B = 37,
	N10 = 38,
	N10B = 39,
	N14 = 40,
	N32 = 41,
	N34 = 42,
	N35 = 43,
	N36 = 44,
	N20 = 45,
	N13 = 46,
	N18 = 47,
	N19 = 48,
	S15A = 49,
	S17A = 50,
	S19A = 51,
	S22A = 52,
	S23A = 53,
	N64A = 54,
	S1A = 55,
	S3A = 56,
	S5A = 57,
	S7A = 58,
	S8A = 59,
	S9A = 60,
	S10A = 61,
	S13A = 62,
	S2A = 63,
	S6A = 64,
	SCN = 65,
	SCC = 66,
	SCS = 67,
	N16B = 68,
	N21 = 69,
	N22 = 70,
	N23 = 71,
	N24 = 72,
	N17 = 73,
	N16 = 74,
	N27 = 75,
	N30 = 76,
	N29 = 77,
	N33 = 78,
	N15 = 79,
	N55 = 80,
	N74 = 81,
	N75 = 82,
	N61 = 83,
	N39 = 84,
	N40 = 85,
	N41 = 86,
	N43 = 87,
	N44 = 88,
	N80 = 89,
	N81 = 90,
	N84 = 91,
	N88 = 92,
	N89 = 93,
	N90 = 94,
	N72 = 95,
	N73 = 96,
	N77 = 97,
	N78 = 98,
	N79 = 99,
	N53 = 100,
	N54 = 101,
	N67 = 102,
	N58B = 103,
	N60 = 104,
	N63 = 105,
	N68 = 106,
	N46 = 107,
	N47 = 108,
	N69 = 109,
	N48 = 110,
	N49 = 111,
	N51 = 112,
	N87 = 113,
	N132 = 114,
	N133 = 115,
	N135 = 116,
	N136 = 117,
	N145 = 118,
	N147 = 119,
	N149 = 120,
	N150 = 121,
	N105 = 122,
	N106 = 123,
	N110 = 124,
	N112 = 125,
	N114 = 126,
	N116 = 127,
	N127 = 128,
	N127B = 129,
	N129 = 130,
	N130 = 131,
	N138 = 132,
	N140 = 133,
	N143 = 134,
	N121 = 135,
	N97 = 136,
	N118 = 137,
	N119 = 138,
	N122 = 139,
	N128 = 140,
	N102 = 141,
	N103 = 142,
	N107 = 143,
	N111 = 144,
	N123 = 145,
	N134 = 146,
	N141 = 147,
	N95 = 148,
	N101 = 149,
	N93 = 150,
	N91 = 151,
	N92 = 152,
	N109 = 153,
	N153 = 154,
	N124 = 155,
	N113 = 156,
	N117 = 157,
	N125 = 158,
	N148 = 159,
	N152 = 160,
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

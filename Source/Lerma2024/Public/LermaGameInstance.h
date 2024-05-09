// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Http.h"
#include "LermaGameInstance.generated.h"

UENUM(BlueprintType)
enum class TipoSignal : uint8 {
	Nada = 0,
	Nivel = 1,
	Presion = 2,
	Gasto = 3,
	Totalizado = 5 , // asi se requirio con boy
	Enlace = 6, // 1 en linea, else fuera de linea
	Compuerta = 7,
	Tiempo = 8,
	Bomba = 9, // 0 No disponible, 1 encendida, 2 apagada, 3 con falla
	Bateria = 10,
	PerillaBomba = 11, // 0 Fuera (OFF), 1 Remoto (REM), 2 Local (LOC), else No disponible
	ModoOperacion = 12, // 0 Apagado (OFF), 1 Remoto (REM), 2 Auto (AUTO), else No disponible
	PerillaBombaControl = 13, // 0 Fuera (OFF), 1 Auto (Aut), 2 Manual (Man), else No disponible
	Valvula = 14, // 1 cerrado, 2 abierta, else No disponible
	ModoControl = 15, // ON when >=16; 0 y 16=Apagado (OFF), 1 y 17 = UTR, 2 y 18 = Variador, else = No disponible
	Automatismo = 16 // 0 Apagado, 1 Remoto, 2 Automático, 3 Variador
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
	// Se agrego la fecha y Valido
	UPROPERTY(BlueprintReadWrite) int IdSignal = 0;
	UPROPERTY(BlueprintReadWrite) float Valor = 0;
	UPROPERTY(BlueprintReadWrite) int DentroRango = 0; //Llega como entero
	UPROPERTY(BlueprintReadWrite) FDateTime Fecha = 0; 
	UPROPERTY(BlueprintReadWrite) int IndiceImagen = 0;
	UPROPERTY(BlueprintReadWrite) bool Valido = 0;
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
	IXT = 1,
	IXTALZ = 2,
	ALZ = 3,
	VCIXT = 4,
	VCALZ = 5,
	VC = 6,
	RVCALM = 7,
	RALM = 8,
	S24A = 9,
	S26A = 10,
	S27A = 11,
	S28A = 12,
	S31A = 13,
	S32A = 14,
	S33A = 15,
	S34A = 16,
	S35A = 17,
	S36A = 18,
	S37A = 19,
	S38A = 20,
	S40A = 21,
	S47A = 22,
	S50A = 23,
	S54A = 24,
	S57A = 25,
	S58A = 26,
	S59A = 27,
	S60A = 28,
	S63A = 29,
	S69A = 30,
	S70A = 31,
	S71A = 32,
	S74A = 33,
	S75A = 34,
	N1 = 35,
	N1B = 36,
	N2 = 37,
	N3 = 38,
	N4 = 39,
	N5 = 40,
	N6 = 41,
	N7 = 42,
	N8 = 43,
	N9 = 44,
	N9B = 45,
	N10 = 46,
	N10B = 47,
	N14 = 48,
	N32 = 49,
	N34 = 50,
	N35 = 51,
	N36 = 52,
	N20 = 53,
	N13 = 54,
	N18 = 55,
	N19 = 56,
	S15A = 57,
	S17A = 58,
	S19A = 59,
	S22A = 60,
	S23A = 61,
	N64A = 62,
	S1A = 63,
	S3A = 64,
	S5A = 65,
	S7A = 66,
	S8A = 67,
	S9A = 68,
	S10A = 69,
	S13A = 70,
	S2A = 71,
	S6A = 72,
	SCN = 73,
	SCC = 74,
	SCS = 75,
	N16B = 76,
	N21 = 77,
	N22 = 78,
	N23 = 79,
	N24 = 80,
	N17 = 81,
	N16 = 82,
	N27 = 83,
	N30 = 84,
	N29 = 85,
	N33 = 86,
	N15 = 87,
	N55 = 88,
	N74 = 89,
	N75 = 90,
	N61 = 91,
	N39 = 92,
	N40 = 93,
	N41 = 94,
	N43 = 95,
	N44 = 96,
	N80 = 97,
	N81 = 98,
	N84 = 99,
	N88 = 100,
	N89 = 101,
	N90 = 102,
	N72 = 103,
	N73 = 104,
	N77 = 105,
	N78 = 106,
	N79 = 107,
	N53 = 108,
	N54 = 109,
	N67 = 110,
	N58B = 111,
	N60 = 112,
	N63 = 113,
	N68 = 114,
	N46 = 115,
	N47 = 116,
	N69 = 117,
	N48 = 118,
	N49 = 119,
	N51 = 120,
	N87 = 121,
	N132 = 122,
	N133 = 123,
	N135 = 124,
	N136 = 125,
	N145 = 126,
	N147 = 127,
	N149 = 128,
	N150 = 129,
	N105 = 130,
	N106 = 131,
	N110 = 132,
	N112 = 133,
	N114 = 134,
	N116 = 135,
	N127 = 136,
	N127B = 137,
	N129 = 138,
	N130 = 139,
	N138 = 140,
	N140 = 141,
	N143 = 142,
	N121 = 143,
	N97 = 144,
	N118 = 145,
	N119 = 146,
	N122 = 147,
	N128 = 148,
	N102 = 149,
	N103 = 150,
	N107 = 151,
	N111 = 152,
	N123 = 153,
	N134 = 154,
	N141 = 155,
	N95 = 156,
	N101 = 157,
	N93 = 158,
	N91 = 159,
	N92 = 160,
	N109 = 161,
	N153 = 162,
	N124 = 163,
	N113 = 164,
	N117 = 165,
	N125 = 166,
	N148 = 167,
	N152 = 168,
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

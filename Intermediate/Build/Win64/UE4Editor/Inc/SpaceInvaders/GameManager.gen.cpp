// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SpaceInvaders/GameManager.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGameManager() {}
// Cross Module References
	SPACEINVADERS_API UClass* Z_Construct_UClass_AGameManager_NoRegister();
	SPACEINVADERS_API UClass* Z_Construct_UClass_AGameManager();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_SpaceInvaders();
	COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
	SPACEINVADERS_API UClass* Z_Construct_UClass_APlayerPawn_NoRegister();
	SPACEINVADERS_API UClass* Z_Construct_UClass_AEnemy_NoRegister();
// End Cross Module References
	void AGameManager::StaticRegisterNativesAGameManager()
	{
	}
	UClass* Z_Construct_UClass_AGameManager_NoRegister()
	{
		return AGameManager::StaticClass();
	}
	struct Z_Construct_UClass_AGameManager_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_NumberOfWaves_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_NumberOfWaves;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_OutputHUD_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_OutputHUD;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_TutorialHUD_MetaData[];
#endif
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_TutorialHUD;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_NumberOfEnemiesInFirstWave_MetaData[];
#endif
		static const UE4CodeGen_Private::FUnsizedIntPropertyParams NewProp_NumberOfEnemiesInFirstWave;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_DifficultyIncreasePerWave_MetaData[];
#endif
		static const UE4CodeGen_Private::FFloatPropertyParams NewProp_DifficultyIncreasePerWave;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_PlayerBP_MetaData[];
#endif
		static const UE4CodeGen_Private::FClassPropertyParams NewProp_PlayerBP;
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_EnemyBP_MetaData[];
#endif
		static const UE4CodeGen_Private::FClassPropertyParams NewProp_EnemyBP;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AGameManager_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_SpaceInvaders,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGameManager_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "GameManager.h" },
		{ "ModuleRelativePath", "GameManager.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGameManager_Statics::NewProp_NumberOfWaves_MetaData[] = {
		{ "Category", "GameManager" },
		{ "ModuleRelativePath", "GameManager.h" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_AGameManager_Statics::NewProp_NumberOfWaves = { "NumberOfWaves", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AGameManager, NumberOfWaves), METADATA_PARAMS(Z_Construct_UClass_AGameManager_Statics::NewProp_NumberOfWaves_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AGameManager_Statics::NewProp_NumberOfWaves_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGameManager_Statics::NewProp_OutputHUD_MetaData[] = {
		{ "Category", "GameManager" },
		{ "ModuleRelativePath", "GameManager.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_AGameManager_Statics::NewProp_OutputHUD = { "OutputHUD", nullptr, (EPropertyFlags)0x0010000000000004, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AGameManager, OutputHUD), METADATA_PARAMS(Z_Construct_UClass_AGameManager_Statics::NewProp_OutputHUD_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AGameManager_Statics::NewProp_OutputHUD_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGameManager_Statics::NewProp_TutorialHUD_MetaData[] = {
		{ "Category", "GameManager" },
		{ "ModuleRelativePath", "GameManager.h" },
	};
#endif
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UClass_AGameManager_Statics::NewProp_TutorialHUD = { "TutorialHUD", nullptr, (EPropertyFlags)0x0010000000000004, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AGameManager, TutorialHUD), METADATA_PARAMS(Z_Construct_UClass_AGameManager_Statics::NewProp_TutorialHUD_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AGameManager_Statics::NewProp_TutorialHUD_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGameManager_Statics::NewProp_NumberOfEnemiesInFirstWave_MetaData[] = {
		{ "Category", "GameManager" },
		{ "ModuleRelativePath", "GameManager.h" },
	};
#endif
	const UE4CodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UClass_AGameManager_Statics::NewProp_NumberOfEnemiesInFirstWave = { "NumberOfEnemiesInFirstWave", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AGameManager, NumberOfEnemiesInFirstWave), METADATA_PARAMS(Z_Construct_UClass_AGameManager_Statics::NewProp_NumberOfEnemiesInFirstWave_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AGameManager_Statics::NewProp_NumberOfEnemiesInFirstWave_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGameManager_Statics::NewProp_DifficultyIncreasePerWave_MetaData[] = {
		{ "Category", "GameManager" },
		{ "ModuleRelativePath", "GameManager.h" },
	};
#endif
	const UE4CodeGen_Private::FFloatPropertyParams Z_Construct_UClass_AGameManager_Statics::NewProp_DifficultyIncreasePerWave = { "DifficultyIncreasePerWave", nullptr, (EPropertyFlags)0x0010000000000001, UE4CodeGen_Private::EPropertyGenFlags::Float, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AGameManager, DifficultyIncreasePerWave), METADATA_PARAMS(Z_Construct_UClass_AGameManager_Statics::NewProp_DifficultyIncreasePerWave_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AGameManager_Statics::NewProp_DifficultyIncreasePerWave_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGameManager_Statics::NewProp_PlayerBP_MetaData[] = {
		{ "Category", "GameManager" },
		{ "ModuleRelativePath", "GameManager.h" },
	};
#endif
	const UE4CodeGen_Private::FClassPropertyParams Z_Construct_UClass_AGameManager_Statics::NewProp_PlayerBP = { "PlayerBP", nullptr, (EPropertyFlags)0x0014000000000001, UE4CodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AGameManager, PlayerBP), Z_Construct_UClass_APlayerPawn_NoRegister, Z_Construct_UClass_UClass, METADATA_PARAMS(Z_Construct_UClass_AGameManager_Statics::NewProp_PlayerBP_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AGameManager_Statics::NewProp_PlayerBP_MetaData)) };
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AGameManager_Statics::NewProp_EnemyBP_MetaData[] = {
		{ "Category", "GameManager" },
		{ "ModuleRelativePath", "GameManager.h" },
	};
#endif
	const UE4CodeGen_Private::FClassPropertyParams Z_Construct_UClass_AGameManager_Statics::NewProp_EnemyBP = { "EnemyBP", nullptr, (EPropertyFlags)0x0014000000000001, UE4CodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AGameManager, EnemyBP), Z_Construct_UClass_AEnemy_NoRegister, Z_Construct_UClass_UClass, METADATA_PARAMS(Z_Construct_UClass_AGameManager_Statics::NewProp_EnemyBP_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_AGameManager_Statics::NewProp_EnemyBP_MetaData)) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AGameManager_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGameManager_Statics::NewProp_NumberOfWaves,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGameManager_Statics::NewProp_OutputHUD,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGameManager_Statics::NewProp_TutorialHUD,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGameManager_Statics::NewProp_NumberOfEnemiesInFirstWave,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGameManager_Statics::NewProp_DifficultyIncreasePerWave,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGameManager_Statics::NewProp_PlayerBP,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AGameManager_Statics::NewProp_EnemyBP,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AGameManager_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AGameManager>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AGameManager_Statics::ClassParams = {
		&AGameManager::StaticClass,
		"Engine",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AGameManager_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_AGameManager_Statics::PropPointers),
		0,
		0x009000A4u,
		METADATA_PARAMS(Z_Construct_UClass_AGameManager_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_AGameManager_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AGameManager()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AGameManager_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AGameManager, 2512861519);
	template<> SPACEINVADERS_API UClass* StaticClass<AGameManager>()
	{
		return AGameManager::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AGameManager(Z_Construct_UClass_AGameManager, &AGameManager::StaticClass, TEXT("/Script/SpaceInvaders"), TEXT("AGameManager"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AGameManager);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif

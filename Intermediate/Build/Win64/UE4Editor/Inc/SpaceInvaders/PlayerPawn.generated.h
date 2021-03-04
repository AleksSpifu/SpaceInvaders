// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UPrimitiveComponent;
class AActor;
struct FHitResult;
#ifdef SPACEINVADERS_PlayerPawn_generated_h
#error "PlayerPawn.generated.h already included, missing '#pragma once' in PlayerPawn.h"
#endif
#define SPACEINVADERS_PlayerPawn_generated_h

#define SpaceInvaders_4_26_Source_SpaceInvaders_PlayerPawn_h_14_SPARSE_DATA
#define SpaceInvaders_4_26_Source_SpaceInvaders_PlayerPawn_h_14_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execOnOverlapBegin);


#define SpaceInvaders_4_26_Source_SpaceInvaders_PlayerPawn_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execOnOverlapBegin);


#define SpaceInvaders_4_26_Source_SpaceInvaders_PlayerPawn_h_14_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesAPlayerPawn(); \
	friend struct Z_Construct_UClass_APlayerPawn_Statics; \
public: \
	DECLARE_CLASS(APlayerPawn, APawn, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SpaceInvaders"), NO_API) \
	DECLARE_SERIALIZER(APlayerPawn)


#define SpaceInvaders_4_26_Source_SpaceInvaders_PlayerPawn_h_14_INCLASS \
private: \
	static void StaticRegisterNativesAPlayerPawn(); \
	friend struct Z_Construct_UClass_APlayerPawn_Statics; \
public: \
	DECLARE_CLASS(APlayerPawn, APawn, COMPILED_IN_FLAGS(0 | CLASS_Config), CASTCLASS_None, TEXT("/Script/SpaceInvaders"), NO_API) \
	DECLARE_SERIALIZER(APlayerPawn)


#define SpaceInvaders_4_26_Source_SpaceInvaders_PlayerPawn_h_14_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API APlayerPawn(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(APlayerPawn) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, APlayerPawn); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(APlayerPawn); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API APlayerPawn(APlayerPawn&&); \
	NO_API APlayerPawn(const APlayerPawn&); \
public:


#define SpaceInvaders_4_26_Source_SpaceInvaders_PlayerPawn_h_14_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API APlayerPawn(APlayerPawn&&); \
	NO_API APlayerPawn(const APlayerPawn&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, APlayerPawn); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(APlayerPawn); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(APlayerPawn)


#define SpaceInvaders_4_26_Source_SpaceInvaders_PlayerPawn_h_14_PRIVATE_PROPERTY_OFFSET
#define SpaceInvaders_4_26_Source_SpaceInvaders_PlayerPawn_h_11_PROLOG
#define SpaceInvaders_4_26_Source_SpaceInvaders_PlayerPawn_h_14_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SpaceInvaders_4_26_Source_SpaceInvaders_PlayerPawn_h_14_PRIVATE_PROPERTY_OFFSET \
	SpaceInvaders_4_26_Source_SpaceInvaders_PlayerPawn_h_14_SPARSE_DATA \
	SpaceInvaders_4_26_Source_SpaceInvaders_PlayerPawn_h_14_RPC_WRAPPERS \
	SpaceInvaders_4_26_Source_SpaceInvaders_PlayerPawn_h_14_INCLASS \
	SpaceInvaders_4_26_Source_SpaceInvaders_PlayerPawn_h_14_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define SpaceInvaders_4_26_Source_SpaceInvaders_PlayerPawn_h_14_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	SpaceInvaders_4_26_Source_SpaceInvaders_PlayerPawn_h_14_PRIVATE_PROPERTY_OFFSET \
	SpaceInvaders_4_26_Source_SpaceInvaders_PlayerPawn_h_14_SPARSE_DATA \
	SpaceInvaders_4_26_Source_SpaceInvaders_PlayerPawn_h_14_RPC_WRAPPERS_NO_PURE_DECLS \
	SpaceInvaders_4_26_Source_SpaceInvaders_PlayerPawn_h_14_INCLASS_NO_PURE_DECLS \
	SpaceInvaders_4_26_Source_SpaceInvaders_PlayerPawn_h_14_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> SPACEINVADERS_API UClass* StaticClass<class APlayerPawn>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID SpaceInvaders_4_26_Source_SpaceInvaders_PlayerPawn_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS

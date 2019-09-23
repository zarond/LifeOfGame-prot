// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef LOG_LoGGameModeBase_generated_h
#error "LoGGameModeBase.generated.h already included, missing '#pragma once' in LoGGameModeBase.h"
#endif
#define LOG_LoGGameModeBase_generated_h

#define LoG_Source_LoG_LoGGameModeBase_h_15_RPC_WRAPPERS
#define LoG_Source_LoG_LoGGameModeBase_h_15_RPC_WRAPPERS_NO_PURE_DECLS
#define LoG_Source_LoG_LoGGameModeBase_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesALoGGameModeBase(); \
	friend struct Z_Construct_UClass_ALoGGameModeBase_Statics; \
public: \
	DECLARE_CLASS(ALoGGameModeBase, AGameModeBase, COMPILED_IN_FLAGS(0 | CLASS_Transient), CASTCLASS_None, TEXT("/Script/LoG"), NO_API) \
	DECLARE_SERIALIZER(ALoGGameModeBase)


#define LoG_Source_LoG_LoGGameModeBase_h_15_INCLASS \
private: \
	static void StaticRegisterNativesALoGGameModeBase(); \
	friend struct Z_Construct_UClass_ALoGGameModeBase_Statics; \
public: \
	DECLARE_CLASS(ALoGGameModeBase, AGameModeBase, COMPILED_IN_FLAGS(0 | CLASS_Transient), CASTCLASS_None, TEXT("/Script/LoG"), NO_API) \
	DECLARE_SERIALIZER(ALoGGameModeBase)


#define LoG_Source_LoG_LoGGameModeBase_h_15_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ALoGGameModeBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ALoGGameModeBase) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ALoGGameModeBase); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ALoGGameModeBase); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ALoGGameModeBase(ALoGGameModeBase&&); \
	NO_API ALoGGameModeBase(const ALoGGameModeBase&); \
public:


#define LoG_Source_LoG_LoGGameModeBase_h_15_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ALoGGameModeBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API ALoGGameModeBase(ALoGGameModeBase&&); \
	NO_API ALoGGameModeBase(const ALoGGameModeBase&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ALoGGameModeBase); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ALoGGameModeBase); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ALoGGameModeBase)


#define LoG_Source_LoG_LoGGameModeBase_h_15_PRIVATE_PROPERTY_OFFSET
#define LoG_Source_LoG_LoGGameModeBase_h_12_PROLOG
#define LoG_Source_LoG_LoGGameModeBase_h_15_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	LoG_Source_LoG_LoGGameModeBase_h_15_PRIVATE_PROPERTY_OFFSET \
	LoG_Source_LoG_LoGGameModeBase_h_15_RPC_WRAPPERS \
	LoG_Source_LoG_LoGGameModeBase_h_15_INCLASS \
	LoG_Source_LoG_LoGGameModeBase_h_15_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define LoG_Source_LoG_LoGGameModeBase_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	LoG_Source_LoG_LoGGameModeBase_h_15_PRIVATE_PROPERTY_OFFSET \
	LoG_Source_LoG_LoGGameModeBase_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	LoG_Source_LoG_LoGGameModeBase_h_15_INCLASS_NO_PURE_DECLS \
	LoG_Source_LoG_LoGGameModeBase_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> LOG_API UClass* StaticClass<class ALoGGameModeBase>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID LoG_Source_LoG_LoGGameModeBase_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS

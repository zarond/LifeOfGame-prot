// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef PROTOTYPE_HelloWorld_generated_h
#error "HelloWorld.generated.h already included, missing '#pragma once' in HelloWorld.h"
#endif
#define PROTOTYPE_HelloWorld_generated_h

#define Prototype_Source_Prototype_Public_HelloWorld_h_15_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execGetProjectVersion) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FString*)Z_Param__Result=UHelloWorld::GetProjectVersion(); \
		P_NATIVE_END; \
	}


#define Prototype_Source_Prototype_Public_HelloWorld_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execGetProjectVersion) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		*(FString*)Z_Param__Result=UHelloWorld::GetProjectVersion(); \
		P_NATIVE_END; \
	}


#define Prototype_Source_Prototype_Public_HelloWorld_h_15_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUHelloWorld(); \
	friend struct Z_Construct_UClass_UHelloWorld_Statics; \
public: \
	DECLARE_CLASS(UHelloWorld, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/Prototype"), NO_API) \
	DECLARE_SERIALIZER(UHelloWorld)


#define Prototype_Source_Prototype_Public_HelloWorld_h_15_INCLASS \
private: \
	static void StaticRegisterNativesUHelloWorld(); \
	friend struct Z_Construct_UClass_UHelloWorld_Statics; \
public: \
	DECLARE_CLASS(UHelloWorld, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/Prototype"), NO_API) \
	DECLARE_SERIALIZER(UHelloWorld)


#define Prototype_Source_Prototype_Public_HelloWorld_h_15_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UHelloWorld(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UHelloWorld) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UHelloWorld); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UHelloWorld); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UHelloWorld(UHelloWorld&&); \
	NO_API UHelloWorld(const UHelloWorld&); \
public:


#define Prototype_Source_Prototype_Public_HelloWorld_h_15_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UHelloWorld(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UHelloWorld(UHelloWorld&&); \
	NO_API UHelloWorld(const UHelloWorld&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UHelloWorld); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UHelloWorld); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UHelloWorld)


#define Prototype_Source_Prototype_Public_HelloWorld_h_15_PRIVATE_PROPERTY_OFFSET
#define Prototype_Source_Prototype_Public_HelloWorld_h_12_PROLOG
#define Prototype_Source_Prototype_Public_HelloWorld_h_15_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Prototype_Source_Prototype_Public_HelloWorld_h_15_PRIVATE_PROPERTY_OFFSET \
	Prototype_Source_Prototype_Public_HelloWorld_h_15_RPC_WRAPPERS \
	Prototype_Source_Prototype_Public_HelloWorld_h_15_INCLASS \
	Prototype_Source_Prototype_Public_HelloWorld_h_15_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define Prototype_Source_Prototype_Public_HelloWorld_h_15_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	Prototype_Source_Prototype_Public_HelloWorld_h_15_PRIVATE_PROPERTY_OFFSET \
	Prototype_Source_Prototype_Public_HelloWorld_h_15_RPC_WRAPPERS_NO_PURE_DECLS \
	Prototype_Source_Prototype_Public_HelloWorld_h_15_INCLASS_NO_PURE_DECLS \
	Prototype_Source_Prototype_Public_HelloWorld_h_15_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> PROTOTYPE_API UClass* StaticClass<class UHelloWorld>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID Prototype_Source_Prototype_Public_HelloWorld_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS

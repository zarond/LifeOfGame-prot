// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Prototype/Public/HelloWorld.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeHelloWorld() {}
// Cross Module References
	PROTOTYPE_API UClass* Z_Construct_UClass_UHelloWorld_NoRegister();
	PROTOTYPE_API UClass* Z_Construct_UClass_UHelloWorld();
	ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
	UPackage* Z_Construct_UPackage__Script_Prototype();
	PROTOTYPE_API UFunction* Z_Construct_UFunction_UHelloWorld_GetProjectVersion();
// End Cross Module References
	void UHelloWorld::StaticRegisterNativesUHelloWorld()
	{
		UClass* Class = UHelloWorld::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "GetProjectVersion", &UHelloWorld::execGetProjectVersion },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UHelloWorld_GetProjectVersion_Statics
	{
		struct HelloWorld_eventGetProjectVersion_Parms
		{
			FString ReturnValue;
		};
		static const UE4CodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UE4CodeGen_Private::FFunctionParams FuncParams;
	};
	const UE4CodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UHelloWorld_GetProjectVersion_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UE4CodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(HelloWorld_eventGetProjectVersion_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UHelloWorld_GetProjectVersion_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UHelloWorld_GetProjectVersion_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UHelloWorld_GetProjectVersion_Statics::Function_MetaDataParams[] = {
		{ "Category", "Game" },
		{ "CompactNodeTitle", "HelloWorld" },
		{ "DisplayName", "Hello World" },
		{ "ModuleRelativePath", "Public/HelloWorld.h" },
	};
#endif
	const UE4CodeGen_Private::FFunctionParams Z_Construct_UFunction_UHelloWorld_GetProjectVersion_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UHelloWorld, nullptr, "GetProjectVersion", nullptr, nullptr, sizeof(HelloWorld_eventGetProjectVersion_Parms), Z_Construct_UFunction_UHelloWorld_GetProjectVersion_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UFunction_UHelloWorld_GetProjectVersion_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14042401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UHelloWorld_GetProjectVersion_Statics::Function_MetaDataParams, ARRAY_COUNT(Z_Construct_UFunction_UHelloWorld_GetProjectVersion_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UHelloWorld_GetProjectVersion()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UE4CodeGen_Private::ConstructUFunction(ReturnFunction, Z_Construct_UFunction_UHelloWorld_GetProjectVersion_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UHelloWorld_NoRegister()
	{
		return UHelloWorld::StaticClass();
	}
	struct Z_Construct_UClass_UHelloWorld_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UHelloWorld_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
		(UObject* (*)())Z_Construct_UPackage__Script_Prototype,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UHelloWorld_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UHelloWorld_GetProjectVersion, "GetProjectVersion" }, // 1438733974
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UHelloWorld_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "HelloWorld.h" },
		{ "ModuleRelativePath", "Public/HelloWorld.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UHelloWorld_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UHelloWorld>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_UHelloWorld_Statics::ClassParams = {
		&UHelloWorld::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		nullptr,
		nullptr,
		ARRAY_COUNT(DependentSingletons),
		ARRAY_COUNT(FuncInfo),
		0,
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UHelloWorld_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_UHelloWorld_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UHelloWorld()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_UHelloWorld_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(UHelloWorld, 4267532661);
	template<> PROTOTYPE_API UClass* StaticClass<UHelloWorld>()
	{
		return UHelloWorld::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UHelloWorld(Z_Construct_UClass_UHelloWorld, &UHelloWorld::StaticClass, TEXT("/Script/Prototype"), TEXT("UHelloWorld"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(UHelloWorld);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif

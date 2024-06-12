/*
* Copyright (c) <2021> Side Effects Software Inc.
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice,
*    this list of conditions and the following disclaimer.
*
* 2. The name of Side Effects Software may not be used to endorse or
*    promote products derived from this software without specific prior
*    written permission.
*
* THIS SOFTWARE IS PROVIDED BY SIDE EFFECTS SOFTWARE "AS IS" AND ANY EXPRESS
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
* NO EVENT SHALL SIDE EFFECTS SOFTWARE BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
* OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
* EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#pragma once

#include "HAPI/HAPI_Common.h"

#include "HoudiniGeoPartObject.h"
#include "HoudiniOutput.h"
#include "HoudiniPackageParams.h"
#include "CoreMinimal.h"
#include "Math/MathFwd.h"


struct FHoudiniSkeletonBone
{
	FString Name;
	FMatrix HoudiniGlobalMatrix;
	FTransform UnrealGlobalMatrix;
	FTransform UnrealLocalMatrix;
	int Id = -1;
	int HoudiniBoneNumber = -1;;
	TArray<FHoudiniSkeletonBone *> Children;
	FHoudiniSkeletonBone * Parent = nullptr;
};


struct FHoudiniSkeleton
{
	TArray<FHoudiniSkeletonBone> Bones;
	FHoudiniSkeletonBone * Root = nullptr;
	TMap<FString, FHoudiniSkeletonBone*> BoneMap;
	TMap<int, FString> HoudiniBoneMap;
};

struct FHoudiniSkinInfluence
{
	FHoudiniSkeletonBone * Bone = nullptr;
	float Weight = 0.0f;
};
struct FHoudiniSkinWeights
{
	TArray<FHoudiniSkinInfluence> Influences;
	int NumInfluences = 0;
	int NumVertices = 0;
};

struct HOUDINIENGINE_API FHoudiniSkeletalMeshUtils
{
	static FHoudiniSkeleton ConstructSkeleton(HAPI_NodeId PoseNodeId, HAPI_PartId PosePartId);

	static FHoudiniSkinWeights ConstructSkinWeights(HAPI_NodeId NodeId, HAPI_PartId PartId, FHoudiniSkeleton& Skeleton);

protected:
	static FMatrix ConstructHoudiniMatrix(const float Rotation[], const float Position[]);

	static FTransform HoudiniToUnrealMatrix(const FMatrix & Matrix);



};


#include "CustomSimulation.h"
#include "Transform.h"

#include <vector>

LM_::Vec3 g_Origin(0.f);
LM_::Vec3 g_Red(1.f, 0.f, 0.f);
LM_::Vec3 g_Green(0.f, 1.f, 0.f);
LM_::Vec3 g_Blue(0.f, 0.f, 1.f);

void CustomSimulation::Init()
{
	int			spine01 = GetSkeletonBoneIndex("spine_01");
	int			spineParent = GetSkeletonBoneParentIndex(spine01);
	const char* spineParentName = GetSkeletonBoneName(spineParent);

	float  posX, posY, posZ, quatW, quatX, quatY, quatZ;
	size_t keyCount = GetAnimKeyCount("ThirdPersonWalk.anim");
	GetAnimLocalBoneTransform("ThirdPersonWalk.anim", spineParent, keyCount * 0.5f, posX, posY, posZ, quatW, quatX, quatY, quatZ);

	printf("Spine bone index : %d\n", spine01);
	printf("Spine parent bone : %s\n", spineParentName);
	printf("Spine parent bone index : %d\n", spineParent);
	printf("Skeleton bone count: %d\n", GetSkeletonBoneCount());
	printf("Anim key count : %u\n", keyCount);
	printf("Anim key : pos(%.2f,%.2f,%.2f) rotation quat(%.10f,%.10f,%.10f,%.10f)\n", posX, posY, posZ, quatW, quatX, quatY, quatZ);
}

void CustomSimulation::Update(float frameTime)
{
	if (frameTime > 0.1f)
	{
		frameTime = 1.0f / 60.0f;
	}
	// frameTime /= 100.0f;

	drawWorldMarker();

	step1(frameTime);
	// step2(frameTime);
	// step3(frameTime);
	// step4(frameTime);
	// step5(frameTime);
}

void CustomSimulation::drawWorldMarker()
{
	drawLine(g_Origin, { 100.f, 0, 0 }, g_Red);	  // X axis
	drawLine(g_Origin, { 0, 100.f, 0 }, g_Green); // Y axis
	drawLine(g_Origin, { 0, 0, 100.f }, g_Blue);  // Z axis
}

void CustomSimulation::drawLine(
	LM_::Vec3 const& pStart, LM_::Vec3 const& pEnd, LM_::Vec3 const& pColor, LM_::Vec3 const& pOffset) const
{
	::DrawLine(
		pStart.m_x + pOffset.m_x, pStart.m_y + pOffset.m_y, pStart.m_z + pOffset.m_z, pEnd.m_x + pOffset.m_x,
		pEnd.m_y + pOffset.m_y, pEnd.m_z + pOffset.m_z, pColor.m_x, pColor.m_y, pColor.m_z);
}

void CustomSimulation::drawSkeleton(int firstIndex, int lastIndex, LM_::Mat4 inverseBindMatrix)
{
	// int	  bone = firstIndex;
	// float bonePosX, bonePosY, bonePosZ, boneQuatW, boneQuatX, boneQuatY, boneQuatZ;
	// float bone2PosX, bone2PosY, bone2PosZ, bone2QuatW, bone2QuatX, bone2QuatY, bone2QuatZ;

	// for (; bone < lastIndex - 1; bone++)
	//{
	//	GetSkeletonBoneLocalBindTransform(bone, bonePosX, bonePosY, bonePosZ, boneQuatW, boneQuatX, boneQuatY, boneQuatZ);
	//	Transform boneTransform{ .m_Position = { bonePosX, bonePosY, bonePosZ },
	//							 .m_Rotation = { boneQuatX, boneQuatY, boneQuatZ, boneQuatW } };

	//	GetSkeletonBoneLocalBindTransform(
	//		bone + 1, bone2PosX, bone2PosY, bone2PosZ, bone2QuatW, bone2QuatX, bone2QuatY, bone2QuatZ);
	//	Transform bone2Transform{ .m_Position = { bone2PosX, bone2PosY, bone2PosZ },
	//							  .m_Rotation = { bone2QuatX, bone2QuatY, bone2QuatZ, bone2QuatW } };

	//	LM_::Vec4 bonePosition, bone2Position;

	//	bonePosition = LM_::Vec4(boneTransform.m_Position) * inverseBindMatrix;
	//	bone2Position = LM_::Vec4(bone2Transform.m_Position) * inverseBindMatrix;

	//	drawLine({ bonePosX, bonePosY, bonePosZ }, { bone2PosX, bone2PosY, bone2PosZ }, { 1.f, 0.f, 1.f }, { 0.f, -10.f, 0.f });

	//	// printf(
	//	//	"Bone (%d) pos(%.2f,%.2f,%.2f)\nNext bone (%d) pos(%.2f,%.2f,%.2f)\n", bone, bonePosX, bonePosY, bonePosZ, bone + 1,
	//	//	bone2PosX, bone2PosY, bone2PosZ);
	//}
}

void CustomSimulation::step1(float frameTime)
{
	// int spine01 = GetSkeletonBoneIndex("spine_01");
	// int spineParent = GetSkeletonBoneParentIndex(spine01);

	// float  posX, posY, posZ, quatW, quatX, quatY, quatZ;
	// GetAnimLocalBoneTransform("ThirdPersonWalk.anim", spineParent, 0, posX, posY, posZ, quatW, quatX, quatY,
	// quatZ);

	// float spinePosX, spinePosY, spinePosZ, spineQuatW, spineQuatX, spineQuatY, spineQuatZ;
	// GetAnimLocalBoneTransform(
	//"ThirdPersonWalk.anim", spine01, 0, spinePosX, spinePosY, spinePosZ, spineQuatW, spineQuatX, spineQuatY,
	// spineQuatZ);

	// drawLine({ posX, posY, posZ }, { spinePosX, spinePosY, spinePosZ }, { 1.f, 1.f, 0.f }, { 0.f, -10.f, 0.f });

	///

	// int bone = GetSkeletonBoneIndex("spine_01");
	// int parentIndex;
	// while (bone != -1)
	//{
	//	parentIndex = bone;
	//	bone = GetSkeletonBoneParentIndex(bone);
	// }
	// int lastIndex = GetSkeletonBoneCount() + parentIndex;
	// drawSkeleton(parentIndex, lastIndex);

	///

	////int	  pelvis = GetSkeletonBoneIndex("pelvis");
	// float posX, posY, posZ, quatW, quatX, quatY, quatZ;
	// GetAnimLocalBoneTransform("ThirdPersonWalk.anim", 0, 0, posX, posY, posZ, quatW, quatX, quatY, quatZ);
	// Transform pelvisTransform{ .m_Position = { posX, posY, posZ }, .m_Rotation = { quatX, quatY, quatZ, quatW } };
	// LM_::Mat4 inverseBindPose = pelvisTransform;
	// inverseBindPose = inverseBindPose.GetInverse();

	////GetSkeletonBoneLocalBindTransform(1, posX, posY, posZ, quatW, quatX, quatY, quatZ);
	////pelvisTransform.m_Position = { posX, posY, posZ };
	////pelvisTransform.m_Rotation = { quatX, quatY, quatZ, quatW };

	////int	  spine01 = GetSkeletonBoneIndex("spine01");
	////float spinePosX, spinePosY, spinePosZ, spineQuatW, spineQuatX, spineQuatY, spineQuatZ;
	////GetSkeletonBoneLocalBindTransform(spine01, spinePosX, spinePosY, spinePosZ, spineQuatW, spineQuatX, spineQuatY, spineQuatZ);

	////Transform spine01Transform{ .m_Position = { spinePosX, spinePosY, spinePosZ },
	////							.m_Rotation = { spineQuatX, spineQuatY, spineQuatZ, spineQuatW } };

	////// std::cout << "\n\nInverse bind pose:\n" << inverseBindPose << std::endl;

	////LM_::Vec4 pelvisPosition, spine01Position;

	////pelvisPosition = LM_::Vec4(pelvisTransform.m_Position) * inverseBindPose;
	////spine01Position = LM_::Vec4(spine01Transform.m_Position) * inverseBindPose;

	//// drawLine(pelvisPosition, spine01Position, { 1.f, 1.f, 0.f }, { 0.f, -10.f, 0.f });
	// drawSkeleton(1, 63, inverseBindPose);

	///

	std::vector<Transform> bones;
	size_t				   boneCount = GetSkeletonBoneCount() - 7;

	bones.reserve(boneCount);

	float posX, posY, posZ, quatW, quatX, quatY, quatZ;

	for (int index = 0; index < boneCount; index++)
	{
		GetSkeletonBoneLocalBindTransform(index, posX, posY, posZ, quatW, quatX, quatY, quatZ);
		bones.push_back({ { posX, posY, posZ }, { quatW, quatX, quatY, quatZ } });

		int parent = GetSkeletonBoneParentIndex(index);
		if (parent != -1)
		{
			bones[index] *= bones[parent];
			drawLine(bones[index].m_Position, bones[parent].m_Position, { 1.f, 0.f, 1.f }, { 0.f, -100.f, 0.f });
		}
	}
}

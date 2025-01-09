#include "CustomSimulation.h"

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
	GetAnimLocalBoneTransform("ThirdPersonWalk.anim", spineParent, keyCount / 2, posX, posY, posZ, quatW, quatX, quatY, quatZ);

	printf("Spine parent bone : %s\n", spineParentName);
	printf("Anim key count : %ld\n", keyCount);
	printf("Anim key : pos(%.2f,%.2f,%.2f) rotation quat(%.10f,%.10f,%.10f,%.10f)\n", posX, posY, posZ, quatW, quatX, quatY, quatZ);
}

void CustomSimulation::Update(float frameTime)
{
	drawWorldMarker();
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

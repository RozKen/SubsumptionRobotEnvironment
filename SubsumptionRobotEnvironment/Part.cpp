#include "Part.h"

namespace SRE{
namespace Robot{
		/**
		 * CreateSphere(float r, float xInit, float yInit, float zInit)
		 * @param r: radius of the sphere
		 * @param xInit: Initial Position on X
		 * @param yInit: Initial Position on Y
		 * @param zInit: Initial Position on Z
		 * @return pActor: Pointer to Created Actor
		 */
	NxActor* Part::CreateSphere(float r, float xInit, float yInit, float zInit){
		NxActorDesc actorDesc;
		NxBodyDesc bodyDesc;
		NxSphereShapeDesc sphereDesc;

		//�f�t�H���g�l�ŏ����� (�N���A)
		actorDesc.setToDefault();
		bodyDesc.setToDefault();
		sphereDesc.setToDefault();
		//bodyDesc.angularDamping = 0.5f;	//�]���薀�C�W��

		sphereDesc.radius = r;									//���̔��a���w��
		//sphereDesc.userData = (void *)(&sphereDesc);
		//sphereDesc.userData = (void *)(&sphereDesc.radius);
		actorDesc.shapes.pushBack(&sphereDesc);	//�����A�N�^�[�ɒǉ�
		actorDesc.body = &bodyDesc;	//���I�����w��
		actorDesc.density = DENSITY;//7874.0f;		//���x7874 kg/m^3 : �S�̖��x
		actorDesc.globalPose.t = NxVec3(xInit, yInit, zInit);	//Scene��̈ʒu
		//Set userData to NULL if you are not doing anyting with it.
		NxActor* pActor = pScene->createActor( actorDesc );
		return pActor;
	}

	NxActor* Part::CreateSphere(float r, NxVec3 pos){
		return CreateSphere(r, pos.x, pos.y, pos.z);
	}
		/**
		 * CreateBox(float w, float d, float h,float xInit, float yInit, float zInit)
		 * @param w: width of the box
		 * @param d: depth of the box
		 * @param h: height of the box
		 * @param xInit: Initial Position on X
		 * @param yInit: Initial Position on Y
		 * @param zInit: Initial Position on Z
		 * @return pActor: Pointer to Created Actor
		 */
	NxActor* Part::CreateBox(float w, float d, float h,float xInit, float yInit, float zInit){
		/*
		 *	Create a Box Actor
		 * Dynamic Actor: Rigid Bodies
		 */
		//Create a Body Descriptor
		NxBodyDesc bodyDesc;					//Box�p Body Descriptor
	
		//The Actor Descriptor
		NxActorDesc actorDesc;
	
		//Box Shape Descriptor
		NxBoxShapeDesc boxDesc;

		//�f�t�H���g�l�ŏ����� (�N���A)
		actorDesc.setToDefault();
		bodyDesc.setToDefault();
		boxDesc.setToDefault();

		//bodyDesc.angularDamping = 0.5f;	//��]�����W��????
		//bodyDesc.linearVelocity = NxVec3 (-30, -10, -10); //�������x��X��������1
		bodyDesc.linearDamping = 0.1f;

		actorDesc.body = &bodyDesc;

		boxDesc.dimensions = NxVec3( w, d, h );	//20.0 x 20.0 x 20.0�̒�����
		actorDesc.shapes.pushBack( &boxDesc );	//Actor��Body��o�^
		actorDesc.density = DENSITY;//7874.0f;	//���x7874 kg/m^3 �@g/cm3 : �S�̖��x
		actorDesc.globalPose.t = NxVec3( xInit, yInit, zInit);		//�����ʒu(10.0, 10.0, 10.0)
	
		//Set userData to NULL if you are not doing anyting with it.
		NxActor* pActor = pScene->createActor( actorDesc );
		return pActor;
	}

	NxActor* Part::CreateBox(NxVec3 dimensions, NxVec3 pos){
		return CreateBox(dimensions.x, dimensions.y, dimensions.z,
			pos.x, pos.y, pos.z);
	}
}
}
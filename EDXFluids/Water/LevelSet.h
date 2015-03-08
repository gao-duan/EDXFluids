#pragma once

#include "EDXPrerequisites.h"
#include "../Base/ForwardDecl.h"
#include "Memory/Array.h"
#include "Math/Vector.h"

namespace EDX
{
	namespace FluidSim
	{
		template<uint Dimension>
		class LevelSet
		{
		protected:
			Array<Dimension, float> mPhi;
			Array<Dimension, float> mPhiPrev;
			Array<Dimension, Vec<Dimension, int>> mClosestSurfIdx;

		public:
			void Initialize(const Vec<Dimension, int>& vDim);
			template<typename PhiFunc>
			void InitSDF(PhiFunc func)
			{
				for(auto i = 0; i < mPhi.LinearSize(); i++)
				{
					Vec<Dimension, float> vPos = mPhi.Index(i);
					mPhi[i] = func(vPos);
				}
			}
			void ReInitSDF(const Array<Dimension, CellType>& markers, const CellType type, const float fNarrowBand = 1e10f);
			Array<Dimension, float>& GetPhi() { return mPhi; }
			Vec<Dimension, int> GetClosestSurfIdx(const Vec<Dimension, int>& vIdx) const { return mClosestSurfIdx[vIdx]; }
		};
	}
}
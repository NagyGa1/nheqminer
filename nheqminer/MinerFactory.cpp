#include "MinerFactory.h"

extern int use_avx;
extern int use_avx2;

MinerFactory::~MinerFactory()
{
	ClearAllSolvers();
}

std::vector<ISolver *> MinerFactory::GenerateSolvers(int cpu_threads, int cuda_count, int* cuda_en, int* cuda_b, int* cuda_t,
	int opencl_count, int opencl_platf, int* opencl_en, int* opencl_t) {
	std::vector<ISolver *> solversPointers;

#ifdef USE_CUDA_DJEZO
	for (int i = 0; i < cuda_count; ++i)
		solversPointers.push_back(djezoSolver(cuda_en[i], i));
#endif
	for (int i = 0; i < cpu_threads; ++i)
		solversPointers.push_back(GenCPUSolver(use_avx2));

	return solversPointers;
}

void MinerFactory::ClearAllSolvers() {
	for (ISolver * ds : _solvers) {
		if (ds != nullptr) {
			delete ds;
		}
	}
	_solvers.clear();
}

ISolver * MinerFactory::GenCPUSolver(int use_opt) {
	_solvers.push_back(new CPUSolverXenoncat(use_opt));
	return _solvers.back();
}


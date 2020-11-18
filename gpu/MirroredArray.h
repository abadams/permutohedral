#ifndef MIRRORED_ARRAY_H
#define MIRRORED_ARRAY_H

template<typename T>
class MirroredArray {
  public:
    MirroredArray(size_t len) {
	size = len;
	host = new T[len];
	owner = true;	
#ifdef CUDA_MEMORY_H
	allocateCudaMemory((void**)&(device), len*sizeof(T));
#else
	CUDA_SAFE_CALL(cudaMalloc((void**)&(device), len*sizeof(T)));
#endif
    }

    MirroredArray(T *data, size_t len) {
	size = len;
	host = data;
	owner = false;
	CUDA_SAFE_CALL(cudaMalloc((void**)&(device), len*sizeof(T)));
	hostToDevice();
    }

    void hostToDevice() {
	CUDA_SAFE_CALL(cudaMemcpy(device, host, size*sizeof(T), cudaMemcpyHostToDevice));
    }
    
    void deviceToHost() {
	CUDA_SAFE_CALL(cudaMemcpy(host, device, size*sizeof(T), cudaMemcpyDeviceToHost));
    }

    ~MirroredArray() {
	if (owner) delete[] host;
	cudaFree(device);
    }

    T *host;
    T *device;
    size_t size;
    bool owner;
};

#endif

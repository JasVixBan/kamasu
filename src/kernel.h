#ifndef RESOPHONIC_GPUMATH_KERNEL_H_INCLUDED
#define RESOPHONIC_GPUMATH_KERNEL_H_INCLUDED

// #ifdef NVCC
// 
// __global__ void
// gpu_mul_scalar_k(float* data, float scalar);
// 
// __global__ void
// gpu_add_scalar_k(float* data, float scalar);
// 
// __global__ void
// gpu_div_scalar_k(float* data, float scalar); 
// 
// __global__ void
// gpu_sub_scalar_k(float* data, float scalar); 
// 
// #endif

void gpu_mul_scalar(float* data, unsigned size, float scalar);
void gpu_add_scalar(float* data, unsigned size, float scalar);
void gpu_sub_scalar(float* data, unsigned size, float scalar);
void gpu_div_scalar(float* data, unsigned size, float scalar);

void gpu_mul_vector(float* lhs, float* rhs,  unsigned size);
void gpu_add_vector(float* lhs, float* rhs,  unsigned size);
void gpu_sub_vector(float* lhs, float* rhs,  unsigned size);
void gpu_div_vector(float* lhs, float* rhs,  unsigned size);

void kamasu_vector_scalar_add(int n, float alpha, float *x, int incx);
void kamasu_vector_scalar_sub(int n, float alpha, float *x, int incx);
void kamasu_vector_scalar_mul(int n, float alpha, float *x, int incx);
void kamasu_vector_scalar_div(int n, float alpha, float *x, int incx);

void kamasu_vector_vector_add(int n, float* lhs, int inclhs, const float* rhs, int incrhs);
void kamasu_vector_vector_sub(int n, float* lhs, int inclhs, const float* rhs, int incrhs);
void kamasu_vector_vector_mul(int n, float* lhs, int inclhs, const float* rhs, int incrhs);
void kamasu_vector_vector_div(int n, float* lhs, int inclhs, const float* rhs, int incrhs);

enum Op { MULTIPLIES, PLUS, MINUS, DIVIDES } ;

void kamasu_testy_knl(Op op, 
		      float* data, 
		      std::size_t n_entries,
		      unsigned n_dims, 
		      unsigned* factors, int* strides, 
		      float scalar);


#endif

// Copyright 2022 Mishina Nadezhda
#include "../../../modules/task_1/mishina_n_conj_gradients/mishina_n_conj_gradients.h"
double VecMultVec(const std::vector<double>& v1,
  const std::vector<double>& v2) {
    size_t count = v1.size();
    double res = 0;
    for (size_t i = 0; i < count; i++) {
        res += v1[i] * v2[i];
    }
    return res;
}
std::vector<double> VecMultNum(const std::vector<double>& v, double d) {
    size_t count = v.size();
    std::vector<double> res(count);
    for (size_t i = 0; i < count; i++) {
        res[i]= v[i] * d;
    }
    return res;
}
std::vector<double> MatrMultVec(const std::vector<std::vector<double>>& M,
  const std::vector<double>& v) {
    size_t count = v.size();
    std::vector<double> res(count);
    for (size_t i = 0; i < count; i++) {
        res[i] = VecMultVec(M[i], v);
    }
    return res;
}
std::vector<double> VecSum(const std::vector<double>& v1,
  const std::vector<double>& v2) {
    size_t count = v1.size();
    std::vector<double> res(count);
    for (size_t i = 0; i < count; i++) {
        res[i] = v1[i] + v2[i];
    }
    return res;
}
std::vector<double> VecOtr(const std::vector<double>& v) {
    size_t count = v.size();
    std::vector<double> res(count);
    for (size_t i = 0; i < count; i++) {
        res[i] = -v[i];
    }
    return res;
}
std::vector<double> ConjGrad(const std::vector<std::vector<double>>& M,
  const std::vector<double>& v) {
    size_t count = v.size();
    std::vector<double> r(count);
    std::vector<double> z(count);
    std::vector<double> x(count);
    r = VecSum(v, VecOtr(MatrMultVec(M, x)));
    z = r;
    for (size_t i = 0; i < count; i++) {
        double a;
        double b;
        std::vector<double> rnew(count);
        a = VecMultVec(r, r) / VecMultVec(MatrMultVec(M, z), z);
        x = VecSum(x, VecMultNum(z, a));
        rnew = VecSum(r, VecOtr(VecMultNum(MatrMultVec(M, z), a)));
        b = VecMultVec(rnew, rnew) / VecMultVec(r, r);
        z = VecSum(rnew, VecMultNum(z, b));
        r = rnew;
    }
    return x;
}

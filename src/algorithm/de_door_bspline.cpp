
#include <assert.h>

#include "algorithm/de_door_bspline.h"

/**
 * @brief basic_de_door_spline_coefficient
 * 未优化的算法
 * 参考：http://www.cs.mtu.edu/~shene/COURSES/cs3621/NOTES/spline/B-spline/bspline-curve-coef.html
 * 计算u在p degree的各系数
 * @param contrl_point_cnt
 * 控制点数量.
 * @param p
 * degree
 * @param knots
 * 节点数据，长度为：contrl_point_cnt+p+1。
 * knots数量，控制点数量，degree的关系，参考：http://www.cs.mtu.edu/~shene/COURSES/cs3621/NOTES/spline/B-spline/bspline-curve.html
 * @param u
 * 输入的计算值
 * @param coefficients
 * 返回的对应各控制点的系数，长度等于contrl_point_cnt
 */
void basic_de_door_spline_coefficient(int contrl_point_cnt,int p,std::vector<float>& knots,float u,std::vector<float>& coefficients){
    assert(knots.size()==contrl_point_cnt+p+1 && "expect:m=n+p+1");

    for(int i=0;i<coefficients.size();i++){
        coefficients[i]=0;
    }
    if(u==knots[0]){
        coefficients[0]=1;
        return;
    }
    if(u==knots[knots.size()-1]){
        coefficients[coefficients.size()-1]=1;
        return;
    }

    //find where u located in knots
    int k=-1;
    for(int i=0;i<knots.size()-1;i++){
        if(u>=knots[i] && u<knots[i+1]){
            k=i;
            break;
        }
    }

    assert(k>=0 && "u should be in range of knots");
    coefficients[k]=1;// degree 0

    for(int d=1;d<=p;d++){
        if(k-d>=0){
            coefficients[k-d]=(knots[k+1]-u)/(knots[k+1]-knots[k-d+1]) * coefficients[k-d+1];
        }
        for(int i=k-d+1;i<=k-1;i++){
//            coefficients[i]=(u-knots[i])/(knots[i+d]-knots[i])*coefficients[i]+(knots)*coefficients[i+1];
        }
    }

}


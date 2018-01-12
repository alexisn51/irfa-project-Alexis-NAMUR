#include <iostream>
#include <cmath>


using namespace std;

double ApproximateYTM (double CouponValue, double d, double FaceValue, double PresentValue, int N)
{
    double result;
    result = ((CouponValue+((FaceValue-PresentValue)/(N+d)))/((FaceValue+PresentValue)/2));
    return result;
}


double TargetFunction (double CouponValue, double d, double FaceValue, double PresentValue, int N,double r)
{
    double result;
    result = (CouponValue/r)*pow((1+r),(1-d))+(FaceValue-(CouponValue/r))*pow(1/(1+r),N+d)-PresentValue;
    return result;

}

double ZeroCoupon (double d, double FaceValue, double PresentValue, int N)
{
    double result ;
    result = (FaceValue/(pow(PresentValue,N+d)))-1;
    return result;
}

double YieldToMaturity(double CouponValue, double d, double FaceValue, double PresentValue, int N, double Epsilon)
{
    double r1;
    double r2;
    double rtemp;
    int iteration;
    double result;
    iteration = 0;
    if (CouponValue==0)
    {
        result = ZeroCoupon(d, FaceValue, PresentValue,N);
        return result ;
    }
    else
    {
        r1 = ApproximateYTM(CouponValue, d, FaceValue, PresentValue,N)*0.95;
        r2 =ApproximateYTM(CouponValue, d, FaceValue, PresentValue,N);

        while(TargetFunction(CouponValue,d,FaceValue,PresentValue,N,r2)>Epsilon || -TargetFunction(CouponValue,d,FaceValue,PresentValue,N,r2)<-Epsilon )
        {
            if (iteration ==200)
            {
                return(-1);
            }

            ++iteration;
            rtemp = r2-((TargetFunction(CouponValue,d,FaceValue,PresentValue,N,r2))*(r2-r1)/(TargetFunction(CouponValue,d,FaceValue,PresentValue,N,r2)-TargetFunction(CouponValue,d,FaceValue,PresentValue,N,r1)));
            r1 = r2;
            r2 = rtemp;
        }
        return r2;
    }
}



int main()
{
    double CouponValue;
    double d;
    double FaceValue;
    double PresentValue;
    int N;
    double Epsilon;
    double result;
    cout << "Please enter the Coupon Value  ";
    cin >> CouponValue;
    cout << "Please enter the year fraction until next payment  ";
    cin >> d;
    cout << "Please enter the Face Value  ";
    cin >> FaceValue;
    cout << "Please enter the Present Value  ";
    cin >> PresentValue;
    cout << "Please enter the number of full years until maturity  ";
    cin >> N;
    cout << "Please enter the error level (0.01 for example) ";
    cin >> Epsilon;
    result = YieldToMaturity(CouponValue,d,FaceValue,PresentValue,N,Epsilon);
    cout << "the Yield to maturity  is  " <<result;


    return 0;
}

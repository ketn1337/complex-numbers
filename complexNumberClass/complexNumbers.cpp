#include <cmath>
#include <limits>
#include <exception>
#include <iostream>

class ComplexNumber
{
    private:
        double _realPart;
        double _imaginaryPart;

        ComplexNumber AssociatedNumber()
        {
            return ComplexNumber(this->_realPart, this->_imaginaryPart * (-1));
        }

        ComplexNumber Multiplication(double num)
        {
            return ComplexNumber(this->GetRealPart() * num, this->GetImaginaryPart() * num);
        }

    public:
        ComplexNumber(double realPart, double imaginaryPart)
        {
            this->_realPart = realPart;
            this->_imaginaryPart = imaginaryPart;
        }

        double GetRealPart() 
        {
            return this->_realPart;
        }

        double GetImaginaryPart()
        {
            return this->_imaginaryPart;
        }

        void SetRealPart(double realPart)
        {
            this->_realPart = realPart;
        }

        void SetImaginaryPart(double imaginaryPart)
        {
            this->_imaginaryPart = imaginaryPart;
        }

        ComplexNumber Addition(ComplexNumber num)
        {
            return ComplexNumber(this->_realPart + num.GetRealPart(), 
                                 this->_imaginaryPart + num.GetImaginaryPart());
        }

        ComplexNumber Multiplication(ComplexNumber num)
        {
            return ComplexNumber(this->_realPart * num.GetRealPart() - this->_imaginaryPart * num.GetImaginaryPart(),
                                 this->_realPart * num.GetImaginaryPart() + this->_imaginaryPart * num.GetRealPart());
        }

        ComplexNumber Difference(ComplexNumber num)
        {
            return this->Addition(num.Multiplication(-1));
        }

        ComplexNumber Division(ComplexNumber num)
        {
            ComplexNumber numerator = this->Multiplication(num.AssociatedNumber());
            double denominator = (num.GetRealPart() * num.GetRealPart()) - (num.GetImaginaryPart() * num.GetImaginaryPart());

            if (std::fabs(denominator) < std::numeric_limits<double>::epsilon())
            {
                throw "Zero division exception";
            }

            return ComplexNumber(numerator.GetRealPart() / denominator, 
                                 numerator.GetImaginaryPart() / denominator);
        }

        ComplexNumber Power(int n)
        {
            double arg = std::atan(this->_imaginaryPart / this->_realPart);
            auto tmp = ComplexNumber(std::cos(n * arg), std::sin(n * arg));

            return ComplexNumber(tmp.Multiplication(std::pow(this->Abs(), n)));
        }

        double Abs()
        {
            return std::sqrt(this->_realPart * this->_realPart + this->_imaginaryPart * this->_imaginaryPart);
        }

        void Print()
        {
            if (this->_imaginaryPart < 0)
                std::cout << this->_realPart << " - " << std::fabs(this->_imaginaryPart) << 'i';
            else
                std::cout << this->_realPart << " + " << this->_imaginaryPart << 'i';
        }

        ComplexNumber operator + (ComplexNumber num)
        {
            return this->Addition(num);
        }

        ComplexNumber operator - (ComplexNumber num)
        {
            return this->Difference(num);
        }

        ComplexNumber operator * (ComplexNumber num)
        {
            return this->Multiplication(num);
        }

        ComplexNumber operator / (ComplexNumber num)
        {
            return this->Division(num);
        }

        ComplexNumber operator ^ (int n)
        {
            return this->Power(n);
        }

        bool isEqual(ComplexNumber num)
        {
            return (this->_realPart - num.GetRealPart() < std::numeric_limits<double>::epsilon()) && 
                   (this->_imaginaryPart - num.GetImaginaryPart() < std::numeric_limits<double>::epsilon());
        }

        bool isEqual(int num)
        {
            return (this->_realPart - num < std::numeric_limits<double>::epsilon()) && 
                   (this->_imaginaryPart < std::numeric_limits<double>::epsilon());
        }

        bool isEqual(double num)
        {
            return (this->_realPart - num < std::numeric_limits<double>::epsilon()) && 
                   (this->_imaginaryPart < std::numeric_limits<double>::epsilon());
        }

        bool operator == (ComplexNumber num)
        {
            return this->isEqual(num);
        }

        bool operator == (int num)
        {
            return this->isEqual(num);
        }

        bool operator == (double num)
        {
            return this->isEqual(num);
        }

        bool operator != (ComplexNumber num)
        {
            return !this->isEqual(num);
        }

        bool operator != (int num)
        {
            return !this->isEqual(num);
        }

        bool operator != (double num)
        {
            return !this->isEqual(num);
        }

};

int main()
{
    auto test1 = ComplexNumber(3, 0);
    auto test2 = ComplexNumber(3, 2);

    auto res = test1 != test2;

    //res.Print();
    std::cout << res;

    return 0;
}
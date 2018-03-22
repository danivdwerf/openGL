#ifndef VECTOR3_H
#define VECTOR3_H

struct Vector3
{
    private: float vec[3];
    public: float X()const{return this->vec[0];}
    public: float Y()const{return this->vec[1];}
    public: float Z()const{return this->vec[2];}

    public: Vector3(float x, float y, float z)
    {
        this->vec[0] = x;
        this->vec[1] = y;
        this->vec[2] = z;
    }
};
#endif
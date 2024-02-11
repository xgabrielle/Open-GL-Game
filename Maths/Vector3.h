#pragma once
class Vector3
{
public:
	float x, y, z;
	Vector3(float x, float y, float z) : x{ x }, y{ y }, z{ z } {}
   
    
    bool operator==(const Vector3& other) const
    {
        // fix the equal operator implementation
        return x == other.x && y == other.y && z ==other.z;
    }

    bool operator!=(const Vector3& other) const
    {
        // fix the equal operator implementation
        return x != other.x && y != other.y && z != other.z;
    }

    // TODO:

    Vector3 operator-() const 
    {
        return Vector3(-x, -y, -z);
    }

    Vector3 operator-(const Vector3& other) const 
    {
        return Vector3( x - other.x , y - other.y , z - other.z);
        
    }
   

    Vector3 operator +(const Vector3& other)const
    {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    Vector3 operator *(float k)const
    {
        return Vector3(x * k, y*k,z*k);
    }

    Vector3 operator /(float k)const
    {
        return Vector3(x / k, y / k, z / k);
    }

    float sqreMag()
    {
        return float ( x * x + y * y + z * z );

    }

    float dotProd( Vector3 a, Vector3 b)
    {
        
    }
};


class Points2d
{
    private:
    float x;
    float y;

    public:
    Points2d();
    Points2d(float, float);
    Points2d(const Points2d &);
    ~Points2d();

    float Getx(){return x;};
    float Gety(){return y;};

    void Setx(float x1){x = x1;};
    void Sety(float y1){y = y1;};

    double norm(unsigned int);
};
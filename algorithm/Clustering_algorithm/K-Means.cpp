#include <iostream>
#include <vector>
#include <cmath>

struct Point
{
    double x;
    double y;
};

double distance(const Point& a, const Point& b)
{
    return std::sqrt(
        (a.x -b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y)
    );
}

std::vector<int> kmeans(const std::vector<Point>& points, int k)
{
    int n = points.size();
    //保存每个点属于哪个簇
    std::vector<int> labels(n,0);
    //随便选择前k个点作为初始中心
    std::vector<Point> centers;
    for(int i = 0; i < k; i++)
    {
        centers.push_back(points[i]);
    }

    bool changed = true;

    while(changed)
    {
        changed = false;

        //1.分配最近中心
        for(int i = 0; i < n; i++)
        {
            int minDist = 1e9;
            int best = 0;

            for(int j = 0; j < k; j++)
            {
                double d = distance(points[i], centers[j]);
                
                if(d < minDist)
                {
                    minDist = d;
                    best = j;
                }
            }

            if(labels[i] != best)
            {
                labels[i] = best;
                changed = true;
            }
        }

         //2.更新中心
        std::vector<double> sumX(k,0);
        std::vector<double> sumY(k,0);
        std::vector<int> count(k,0);

        for(int i = 0; i < n; i++)
        {
            int id = labels[i];
            sumX[i] += points[i].x;
            sumY[i] += points[i].y;
            count[id]++;

        }

        for(int i = 0; i < k; i++)
        {
            if(count[i] > 0)
            {
                centers[i].x = sumX[i] / count[i];
                centers[i].y = sumY[i] / count[i];        
            }
        }
    }

}

int main()
{
    std::vector<Point> points=
    {
        {1,1},
        {2,2},

        {10,10},
        {11,11},

        {20,20},
        {21,21}
    };


    auto result=kmeans(points,3);


    for(int i=0;i<result.size();i++)
    {
        std::cout
            <<"point "
            <<i
            <<" cluster="
            <<result[i]
            <<std::endl;
    }
}
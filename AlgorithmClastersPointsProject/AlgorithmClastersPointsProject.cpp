#include "Console.h"

#include <iostream>
#include <vector>
#include <list>

#undef max;



struct Point
{
    int x, y;
};

std::vector<Point> PointsInit();

int Random(int top)
{
    return rand() % top;
}

double Distance(const Point& left, const Point& right);

template <class Iterator>
Point Centroid(const Iterator begin, const Iterator end);

template <class Iterator>
std::vector<std::list<Point>> Clusters(
    const Iterator begin, const Iterator end, int clastersCount);

void ClustersGraph(std::vector<std::list<Point>> clusters);

template <class Iterator>
void ClusterGraph(const Iterator begin, const Iterator end, Point start, Colors color);

int main()
{
    srand(time(nullptr));

    std::vector<Point> points = PointsInit();

    int clustersCount{ 3 };
    std::vector<std::list<Point>> clustersPoints
        = Clusters(points.begin(), points.end(), clustersCount);

    for (int c{}; c < clustersCount; c++)
    {
        std::cout << "Cluster #" << c << ": ";
        for (std::list<Point>::iterator p = clustersPoints[c].begin();
            p != clustersPoints[c].end(); p++)
            std::cout << "[" << p->x << "," << p->y << "] ";
        std::cout << "\n";
    }

    ClustersGraph(clustersPoints);
}

std::vector<Point> PointsInit()
{
    std::vector<Point> points;

    /*points.push_back(Point{ 3, 4 });
    points.push_back(Point{ 3, 14 });
    points.push_back(Point{ 13, 4 });*/


    points.push_back(Point{ 2, 3 });
    points.push_back(Point{ 3, 4 });
    points.push_back(Point{ 6, 4 });
    points.push_back(Point{ 4, 6 });
    points.push_back(Point{ 11, 8 });
    points.push_back(Point{ 13, 9});
    points.push_back(Point{ 4, 10 });
    points.push_back(Point{ 5, 11 });
    points.push_back(Point{ 11, 11 });
    points.push_back(Point{ 14, 11 });
    points.push_back(Point{ 2, 12 });
    points.push_back(Point{ 4, 13 });

    return points;
}

double Distance(const Point& left, const Point& right)
{
    return sqrt(pow(left.x - right.x, 2) + pow(left.y - right.y, 2));
}

template<class Iterator>
Point Centroid(const Iterator begin, const Iterator end)
{
    double distanceMin{ std::numeric_limits<double>::max() };
    Point centroid{};

    for (Iterator current = begin; current != end; current++)
    {
        double distanceAmount{};
        for (Iterator other = begin; other != end; other++)
            distanceAmount += Distance(*current, *other);
        if (distanceAmount < distanceMin)
        {
            distanceMin = distanceAmount;
            centroid = *current;
        }
    }

    return centroid;
}

template<class Iterator>
std::vector<std::list<Point>> Clusters(const Iterator begin, const Iterator end, int clastersCount)
{
    std::vector<std::list<Point>> clusters(clastersCount);

    for (Iterator it = begin; it != end; it++)
        clusters[Random(clastersCount)].push_back(*it);

    std::vector<Point> centroids(clastersCount);
    
    bool isModified;

    do {

        // finds centroids
        for (int c{}; c < clastersCount; c++)
            centroids[c] = Centroid(clusters[c].begin(), clusters[c].end());

        isModified = false;
        std::vector<std::list<Point>> clustersNew(clastersCount);

        for (int clusterOld{}; clusterOld < clastersCount; clusterOld++)
        {
            
            for (auto point = clusters[clusterOld].begin();
                point != clusters[clusterOld].end(); point++)
            {
                double dinstanceMin{ std::numeric_limits<double>::max() };
                int clusterId{};

                for (int centroid{}; centroid < clastersCount; centroid++)
                {
                    double distance = Distance(*point, centroids[centroid]);
                    if (dinstanceMin > distance)
                    {
                        dinstanceMin = distance;
                        clusterId = centroid;
                    }
                }

                clustersNew[clusterId].push_back(*point);
                if (clusterOld != clusterId)
                    isModified = true;
            }
        }

        clusters = clustersNew;

    } while (isModified);

    return clusters;
}

template<class Iterator>
void ClusterGraph(const Iterator begin, const Iterator end, Point start, Colors color)
{
    char pointChar = 176;
    std::string pointStr(2, pointChar);

    Console console;
    console.Foreground(color);

    for (Iterator it = begin; it != end; it++)
    {
        console.WritePosition(start.y + it->y, (start.x + it->x * 2), pointStr);
    }
}

void ClustersGraph(std::vector<std::list<Point>> clusters)
{
    Console console;

    size_t size{ 20 };
    Point start{ 10, 6 };

    char horizontal = 196;
    char vertical = 179;
    char left_top = 218;

    for (int i{}; i < size + 1; i++) {
        console.WritePosition(start.y + i, start.x - 3, std::to_string(i));
        console.WritePosition(start.y + i, start.x, vertical);
    }
        

    for (int i{}; i < size + 1; i++)
    {
        console.WritePosition(start.y - 1, start.x + 2 * i, std::to_string(i));
        console.WritePosition(start.y, start.x + 2 * i, horizontal);
        console.WritePosition(start.y, start.x + 2 * i + 1, horizontal);
    }
        
    console.WritePosition(start.y, start.x, left_top);
    

    ClusterGraph(clusters[0].begin(), clusters[0].end(), start, Colors::Cyan);
    ClusterGraph(clusters[1].begin(), clusters[1].end(), start, Colors::Magenta);
    ClusterGraph(clusters[2].begin(), clusters[2].end(), start, Colors::Yellow);
    

    console.SetPosition(start.y + size + 1, 0);

}

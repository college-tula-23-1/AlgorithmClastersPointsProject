#include <iostream>
#include <vector>
#include <list>

struct Point
{
    int x, y;
};

std::vector<Point> PointsInit();

int Random(int top)
{
    srand(time(nullptr));
    return rand() % top;
}

double Distance(const Point& left, const Point& right);

template <class Iterator>
Point Centroid(const Iterator begin, const Iterator end);

template <class Iterator>
std::vector<std::list<Point>> Clusters(
    const Iterator begin, const Iterator end, int clastersCount);


int main()
{
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
}

std::vector<Point> PointsInit()
{
    std::vector<Point> points;

    points.push_back(Point{ 2, 3 });
    points.push_back(Point{ 3, 4 });
    points.push_back(Point{ 6, 4 });
    points.push_back(Point{ 4, 6 });
    points.push_back(Point{ 11, 8 });
    points.push_back(Point{ 13, 9});
    points.push_back(Point{ 4, 10 });
    points.push_back(Point{ 7, 11 });
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

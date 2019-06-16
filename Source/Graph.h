#pragma once
#include <vector>
#include <queue>
#include <stack>

class Graph
{
private:
    std::vector<std::vector<int>> edges;
    std::vector<std::vector<bool>> visited;
    std::vector<std::vector<bool>> pixels;
    std::stack<int> path;
    int width;
    int height;
    int numOfVertices;
public:
    Graph(std::vector<std::vector<bool>> pixels, int width, int height) : width(width), height(height)
    {
        for (int i = 0; i < height; ++i)
        {
            std::vector<bool> pixelRow = pixels[i];
            this->pixels.push_back(pixelRow);
        }
        numOfVertices = (width + 1) * (height + 1);
    }
    Graph() {}

private:
    void buildEulerGraph()
    {
        for (int i = 0; i <= height; ++i)
        {
            for (int j = 0; j <= width; ++j)
            {
                int index = i * (width + 1) + j;
                std::vector<int> currentVertex;
                std::vector<bool> currentVertexVisited;
                if (i % 2 == 0)
                {
                    if (i > 0 && j > 0)
                    {
                        if (pixels[i - 1][j - 1])
                        {
                            currentVertex.push_back(index - width - 2);
                            currentVertexVisited.push_back(false);
                        }
                    }
                    if (i > 0 && j < width)
                    {
                        if (pixels[i - 1][j])
                        {
                            currentVertex.push_back(index - width);
                            currentVertexVisited.push_back(false);
                        }
                    }
                    if (i < height && j < width)
                    {
                        if (pixels[i][j])
                        {
                            currentVertex.push_back(index + width + 2);
                            currentVertexVisited.push_back(false);
                        }
                    }
                    if (i < height && j > 0)
                    {
                        if (pixels[i][j - 1])
                        {
                            currentVertex.push_back(index + width);
                            currentVertexVisited.push_back(false);
                        }
                    }

                }
                else
                {
                    if (i > 0 && j > 0)
                    {
                        if (pixels[i - 1][j - 1])
                        {
                            currentVertex.push_back(index - width - 1);
                            currentVertexVisited.push_back(false);
                        }
                    }
                    if (i > 0 && j < width)
                    {
                        if (pixels[i - 1][j])
                        {
                            currentVertex.push_back(index - width - 1);
                            currentVertexVisited.push_back(false);
                        }
                    }
                    if (i < height && j < width)
                    {
                        if (pixels[i][j])
                        {
                            currentVertex.push_back(index + width + 1);
                            currentVertexVisited.push_back(false);
                        }
                    }
                    if (i < height && j > 0)
                    {
                        if (pixels[i][j - 1])
                        {
                            currentVertex.push_back(index + width + 1);
                            currentVertexVisited.push_back(false);
                        }
                    }
                }
                edges.push_back(currentVertex);
                visited.push_back(currentVertexVisited);
            }

        }
    }

    void dfs()
    {
        std::stack<int> passed;
        int u = 0;
        for (int i = 0; i < numOfVertices; ++i)
        {
            if (!edges[i].empty())
            {
                u = i;
                break;
            }
        }
        if (edges[u].empty())
        {
            return;
        }
        passed.push(u);
        while (!passed.empty())
        {
            int w = passed.top();
            for (int i = 0; i < edges[w].size(); ++i)
            {
                if (visited[w][i])
                {
                    continue;
                }
                int v = edges[w][i];
                visited[w][i] = true;
                passed.push(v);
                break;
            }
            if (w == passed.top())
            {
                passed.pop();
                path.push(w);
            }
        }
    }
public:
    void findPath()
    {
        buildEulerGraph();
        dfs();
    }

    int getFirst()
    {
        return path.top();
    }

    bool hasNext()
    {
        return (!path.empty());
    }

    int next()
    {
        int v = path.top();
        path.pop();
        return v;
    }

    
};
#pragma once
#pragma once
#include "GameComponent.h"
#include "imgui_plot.h"
#include <chrono>
#include <fstream>
#include <vector>
#include <deque>
#include <algorithm>
#include <numeric>
#include <memory>
#include <iostream>


struct TestTransform
{
    float matrix[16] =
    {
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1
    };
};
class GameObject3D
{
public:
    TestTransform transform;
    int id{ 5 };
    GameObject3D operator*=(int nr) {
        GameObject3D result{};
        id *= nr;
        result.id = id;
        return result;
    }
};
class GameObject3DAlt
{
public:
    TestTransform* transform{};
    int id{ 5 };
    GameObject3DAlt operator*=(int nr) {
        GameObject3DAlt result{};
        id *= nr;
        result.id = id;
        return result;
    }
};



namespace bdnG
{
    class TTCComponent :public bdnE::GameComponent
    {
    public:
        explicit TTCComponent(bdnE::GameObject* owner);
        void RenderImGui() override;


    private:



        void CalculateIntGraph();        
        void CalculateGameObject3DGraph();        
        void CalculateGameObject3DGraphAlt();
        
        template<typename T>
        std::vector<float> SpeedTestOperations(std::vector<T> testVector, const int nrOfTests)
        {
            std::vector<float> results{};
            if (nrOfTests <= 2) {
                throw std::invalid_argument("Error: please use at least 3 nrOfTests");
            }
            // Create an output file stream

            for (int stepSize = 1; stepSize <= 1024; stepSize *= 2)
            {
                std::deque<int> tempResults{};
                for (int testNr = 0; testNr < nrOfTests; testNr++)
                {


                    auto startTime = std::chrono::high_resolution_clock::now();
                    for (int currentStep = 0; currentStep < static_cast<int>(testVector.size()); currentStep += stepSize)
                    {
                        testVector[currentStep] *= 2;
                    }
                    auto endTime = std::chrono::high_resolution_clock::now();
                    // Calculate duration
                    tempResults.push_back(static_cast<int>(std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count()));
                }
                std::sort(tempResults.begin(), tempResults.end());
                tempResults.pop_front();
                tempResults.pop_back();

                const int result = std::accumulate(tempResults.begin(), tempResults.end(), 0) / static_cast<int>(tempResults.size());

                results.push_back(static_cast<float>(result));

            }
            return results;
        }

        int m_NumSamples{ 10'000'000 };
        int m_NumSamplesGameObject{ 1'000'000 };
        int m_NumTests{ 5 };
        int m_NumTestsGameObject{ 5 };

        bool m_IntIsCalculated = false;
        bool m_GameObject3DIsCalculated = false;
        bool m_GameObject3DAltIsCalculated = false;

        ImGui::PlotConfig m_IntConfig;
        ImGui::PlotConfig m_3DConfig;
        ImGui::PlotConfig m_3DAltConfig;

        std::vector<float> calculationResultInt;
        std::vector<float> calculationResult3D;
        std::vector<float> calculationResult3DAlt;
    };
}



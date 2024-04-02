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



namespace dae
{
    class TTCComponent :public GameComponent
    {
    public:
        explicit TTCComponent(GameObject* owner) : GameComponent(owner)
        {

        }

        void RenderImGui() override
        {
            ImGui::Begin("Exercise 1");

            // Fillable field for typing a number
            ImGui::InputInt("# Samples", &m_NumSamples);
            // Fillable field for typing a number
            ImGui::InputInt("# Tests", &m_NumTests);

            // Button to call CalculateGameObject3DGraph function
            if (ImGui::Button("Trash the cache with Int")) {
                CalculateIntGraph();
            }
            if (m_IntIsCalculated) {
                // Render the graph here
                ImGui::Plot("Int", m_IntConfig);
            }
            ImGui::End();

            ImGui::Begin("Exercise 2");

            // Fillable field for typing a number
            ImGui::InputInt("# Samples", &m_NumSamplesGameObject);
            // Fillable field for typing a number
            ImGui::InputInt("# Tests", &m_NumTestsGameObject);


            // Button to call CalculateGameObject3DGraph function
            if (ImGui::Button("Trash the cache with GameObject3D")) {
                CalculateGameObject3DGraph();
            }

            // Conditional rendering of the graph
            if (m_GameObject3DIsCalculated) {
                // Render the graph here
                ImGui::Plot("plot", m_3DConfig);
            }

            // Button to call CalculateGameObject3DAltGraph function
            if (ImGui::Button("Trash the cache with GameObject3DAlt")) {
                CalculateGameObject3DGraphAlt();
            }

            // Conditional rendering of the graph
            if (m_GameObject3DAltIsCalculated) {
                // Render the graph here
                ImGui::Plot("plot", m_3DAltConfig);
            }
            ImGui::End();
        }

    private:
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


        void CalculateIntGraph()
        {
            std::vector<int> intVector{};
            intVector.resize(m_NumSamples);
            std::fill(intVector.begin(), intVector.end(), 7);

            //Calculate Results
            calculationResultInt = SpeedTestOperations(intVector, m_NumTests);
            for (const auto& result : calculationResultInt)
            {
                std::cout << result << std::endl;
            }


            //Set Graph
            const int numElements = static_cast<int> (calculationResultInt.size());
            const auto maxElementIterator = std::max_element(calculationResultInt.begin(), calculationResultInt.end());

            float largestElement{ 0.f };
            // Check if the iterator is valid
            if (maxElementIterator != calculationResultInt.end()) {
                // Get the value of the largest element
                largestElement = *maxElementIterator;
            }

            m_IntConfig.values.ys = calculationResultInt.data();
            m_IntConfig.values.count = numElements;
            m_IntConfig.scale.min = 0.f;
            m_IntConfig.scale.max = largestElement;
            m_IntConfig.tooltip.show = true;
            m_IntConfig.tooltip.format = "x=%.2f, y=%.2f";
            m_IntConfig.grid_x.show = true;
            m_IntConfig.grid_y.show = true;
            m_IntConfig.frame_size = ImVec2(400, 400);
            m_IntConfig.line_thickness = 2.f;

            m_IntIsCalculated = true;
        }
        void CalculateGameObject3DGraph()
        {
            //Create GameObjectVector
            std::vector<GameObject3D> gameObjectVector{};
            gameObjectVector.resize(m_NumSamplesGameObject);
            std::fill(gameObjectVector.begin(), gameObjectVector.end(), GameObject3D());

            //Calculate Results
            calculationResult3D = SpeedTestOperations(gameObjectVector, m_NumTestsGameObject);

            for (const auto& result : calculationResult3D)
            {
                std::cout << result << std::endl;
            }


            //Set Graph
            const int numElements = static_cast<int> (calculationResult3D.size());
            const auto maxElementIterator = std::max_element(calculationResult3D.begin(), calculationResult3D.end());

            float largestElement{ 0.f };
            // Check if the iterator is valid
            if (maxElementIterator != calculationResult3D.end()) {
                // Get the value of the largest element
                largestElement = *maxElementIterator;
            }

            m_3DConfig.values.ys = calculationResult3D.data();
            m_3DConfig.values.count = numElements;
            m_3DConfig.scale.min = 0.f;
            m_3DConfig.scale.max = largestElement;
            m_3DConfig.tooltip.show = true;
            m_3DConfig.tooltip.format = "x=%.2f, y=%.2f";
            m_3DConfig.grid_x.show = true;
            m_3DConfig.grid_y.show = true;
            m_3DConfig.frame_size = ImVec2(400, 400);
            m_3DConfig.line_thickness = 2.f;

            m_GameObject3DIsCalculated = true;
        }
        void CalculateGameObject3DGraphAlt()
        {
            //Create GameObjectPtrVector
            std::vector<GameObject3DAlt> gameObjectPtrVector{};
            gameObjectPtrVector.resize(m_NumSamplesGameObject);
            std::fill(gameObjectPtrVector.begin(), gameObjectPtrVector.end(), GameObject3DAlt());

            //Calculate Results
            calculationResult3DAlt = SpeedTestOperations(gameObjectPtrVector, m_NumTests);

            //Set Graph
            const int numElements = static_cast<int> (calculationResult3DAlt.size());



            const auto maxElementIterator = std::max_element(calculationResult3DAlt.begin(), calculationResult3DAlt.end());

            float largestElement{ 0.f };
            // Check if the iterator is valid
            if (maxElementIterator != calculationResult3DAlt.end()) {
                // Get the value of the largest element
                largestElement = *maxElementIterator;
            }
            m_3DAltConfig.values.ys = calculationResult3DAlt.data();
            m_3DAltConfig.values.count = numElements;
            m_3DAltConfig.scale.min = 0.f;
            m_3DAltConfig.scale.max = largestElement;
            m_3DAltConfig.tooltip.show = true;
            m_3DAltConfig.tooltip.format = "x=%.2f, y=%.2f";
            m_3DAltConfig.grid_x.show = true;
            m_3DAltConfig.grid_y.show = true;
            m_3DAltConfig.frame_size = ImVec2(400, 400);
            m_3DAltConfig.line_thickness = 2.f;

            m_GameObject3DAltIsCalculated = true;
        }

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
    };
}



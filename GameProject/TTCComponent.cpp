#include "TTCComponent.h"

bdnG::TTCComponent::TTCComponent(bdnE::GameObject* owner) : GameComponent(owner)
{

}

void bdnG::TTCComponent::RenderImGui()
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

void bdnG::TTCComponent::CalculateIntGraph()
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

void bdnG::TTCComponent::CalculateGameObject3DGraph()
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

void bdnG::TTCComponent::CalculateGameObject3DGraphAlt()
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

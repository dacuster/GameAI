using UnityEngine;
using UnityEditor;
using EditorGUITable;   // Download from asset store. $10

// Link this script with another script.
[CustomEditor(typeof(CustomTerrain))]
[CanEditMultipleObjects]

public class CustomTerrainEditor : Editor
{
    /*************************
    **  PROPERTIES (START)  **
    *************************/
    // Used to link serialized property between this script and the linked script.
    SerializedProperty randomHeightRange;
    SerializedProperty heightMapScale;
    SerializedProperty heightMapImage;
    SerializedProperty perlinXScale;
    SerializedProperty perlinYScale;
    SerializedProperty perlinOffsetX;
    SerializedProperty perlinOffsetY;
    SerializedProperty perlinOctaves;
    SerializedProperty perlinPersistance;
    SerializedProperty perlinHeightScale;

    /***********************
    **  PROPERTIES (END)  **
    ***********************/


    /************************
    **  FOLD OUTS (START)  **
    ************************/
    // Show random fold out check.
    private bool showRandom = false;
    private bool showLoadHeights = false;
    private bool showPerlinNoise = false;

    /**********************
    **  FOLD OUTS (END)  **
    **********************/

    private void OnEnable()
    {
        // Get the properties from the linked script.
        randomHeightRange = serializedObject.FindProperty("randomHeightRange");
        heightMapScale = serializedObject.FindProperty("heightMapScale");
        heightMapImage = serializedObject.FindProperty("heightMapImage");
        perlinXScale = serializedObject.FindProperty("perlinXScale");
        perlinYScale = serializedObject.FindProperty("perlinYScale");
        perlinOffsetX = serializedObject.FindProperty("perlinOffsetX");
        perlinOffsetY = serializedObject.FindProperty("perlinOffsetY");
        perlinOctaves = serializedObject.FindProperty("perlinOctaves");
        perlinPersistance = serializedObject.FindProperty("perlinPersistance");
        perlinHeightScale = serializedObject.FindProperty("perlinHeightScale");

        return;
    }

    public override void OnInspectorGUI()
    {
        // Updates all serialized values at the beginning of the function.
        serializedObject.Update();

        // Get the CustomTerrain script.
        CustomTerrain terrain = (CustomTerrain)target;

        // Create a foldout option in the inspector.
        showRandom = EditorGUILayout.Foldout(showRandom, "Random");

        // Foldout is open.
        if (showRandom)
        {
            // Create horizontal divider (slider) bar.
            EditorGUILayout.LabelField("", GUI.skin.horizontalSlider);
            
            // Create a label in the inspector.
            GUILayout.Label("Set Heights Between Random Values", EditorStyles.boldLabel);
            
            // Display the property field.
            EditorGUILayout.PropertyField(randomHeightRange);

            // Generate random terrain height map.
            if (GUILayout.Button("Random Heights"))
            {
                // Create a random terrain.
                terrain.RandomTerrain();
            }
        }

        showLoadHeights = EditorGUILayout.Foldout(showLoadHeights, "Load Heights");

        if (showLoadHeights)
        {
            EditorGUILayout.LabelField("", GUI.skin.horizontalSlider);
            GUILayout.Label("Load Heights From Texture", EditorStyles.boldLabel);
            EditorGUILayout.PropertyField(heightMapImage);
            EditorGUILayout.PropertyField(heightMapScale);

            if (GUILayout.Button("Load Texture"))
            {
                terrain.LoadTexture();
            }
        }

        showPerlinNoise = EditorGUILayout.Foldout(showPerlinNoise, "Single Perlin Noise");

        if (showPerlinNoise)
        {
            EditorGUILayout.LabelField("", GUI.skin.horizontalSlider);
            GUILayout.Label("Perlin Noise", EditorStyles.boldLabel);
            EditorGUILayout.Slider(perlinXScale, 0, 1, new GUIContent("X Scale"));
            EditorGUILayout.Slider(perlinYScale, 0, 1, new GUIContent("Y Scale"));
            EditorGUILayout.IntSlider(perlinOffsetX, 0, 10000, new GUIContent("Offset X"));
            EditorGUILayout.IntSlider(perlinOffsetY, 0, 10000, new GUIContent("Offset Y"));
            EditorGUILayout.IntSlider(perlinOctaves, 0, 10, new GUIContent("Octaves"));
            EditorGUILayout.Slider(perlinPersistance, 0, 10, new GUIContent("Persistance"));
            EditorGUILayout.Slider(perlinHeightScale, 0, 1, new GUIContent("Height Scale"));

            if (GUILayout.Button("Simple Perlin"))
            {
                terrain.SimplePerlin();
            }

            if (GUILayout.Button("Fractal Brownian Motion Perlin"))
            {
                terrain.FractaBrownianMotionPerlin();
            }
        }

        // Create horizontal divider (slider) bar.
        EditorGUILayout.LabelField("", GUI.skin.horizontalSlider);

        // Reset terrain height map to zero.
        if (GUILayout.Button("Reset Heights"))
        {
            // Reset the terrain.
            terrain.ResetTerrain();
        }

        // Apply new changes at the end of the function.
        serializedObject.ApplyModifiedProperties();

        return;
    }


    // Start is called before the first frame update
    void Start()
    {


        return;
    }

    // Update is called once per frame
    void Update()
    {


        return;
    }
}
using UnityEngine;
using UnityEditor;
using EditorGUITable;   // Download from asset store. $10

// Link this script with another script.
[CustomEditor(typeof(CustomTerrain))]
[CanEditMultipleObjects]

public class CustomTerrainEditor : Editor
{
    // Used to link serialized property between this script and the linked script.
    SerializedProperty randomHeightRange;

    // Show random fold out check.
    private bool showRandom = false;

    private void OnEnable()
    {
        randomHeightRange = serializedObject.FindProperty("randomHeightRange");

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
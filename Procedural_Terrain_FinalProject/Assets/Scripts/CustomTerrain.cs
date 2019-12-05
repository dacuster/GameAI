using UnityEditor;
using UnityEngine;
using System;
using System.Collections.Generic;
using System.Linq;

// Make sure the script runs in editor mode as well as play mode.
[ExecuteInEditMode]

public class CustomTerrain : MonoBehaviour
{
    // Random height ranges. (min and max)
    public Vector2 randomHeightRange = new Vector2(0.0f, 0.1f);

    // Texture image to generate height map from pixel colors.
    public Texture2D heightMapImage;

    // 
    public Vector3 heightMapScale = new Vector3(1.0f, 1.0f, 1.0f);

    // The terrain object.
    public Terrain terrain;

    // The terrain data object.
    public TerrainData terrainData;

    // Generate a random terrain height map.
    public void RandomTerrain()
    {
        // 2D height map array. Get current height map.
        float[,] heightMap = terrainData.GetHeights(0, 0, terrainData.heightmapWidth, terrainData.heightmapHeight);

        //heightMap = new float[terrainData.heightmapWidth, terrainData.heightmapHeight];

        for (int x = 0; x < terrainData.heightmapWidth; x++)
        {
            for (int z = 0; z < terrainData.heightmapHeight; z++)
            {
                // Set the height at the x,z coordinate based on the random range minimum and maximum values.
                heightMap[x, z] += UnityEngine.Random.Range(randomHeightRange.x, randomHeightRange.y);
            }
        }

        // Set all the height values added to the height map.
        terrainData.SetHeights(0, 0, heightMap);

        return;
    }

    // Use image to generate heoght map from.
    public void LoadTexture()
    {
        float[,] heightMap;
        heightMap = new float[terrainData.heightmapWidth, terrainData.heightmapHeight];

        for (int x = 0; x < terrainData.heightmapWidth; x++)
        {
            for (int z = 0; z < terrainData.heightmapHeight; z++)
            {
                heightMap[x, z] = heightMapImage.GetPixel((int)(x * heightMapScale.x), (int)(z * heightMapScale.z)).grayscale * heightMapScale.y;
            }
        }

        terrainData.SetHeights(0, 0, heightMap);
    }

    // Reset terrain height map.
    public void ResetTerrain()
    {
        // 2D height map array.
        float[,] heightMap;

        heightMap = new float[terrainData.heightmapWidth, terrainData.heightmapHeight];

        for (int x = 0; x < terrainData.heightmapWidth; x++)
        {
            for (int z = 0; z < terrainData.heightmapHeight; z++)
            {
                // Set the height at the x,z coordinate back to zero.
                heightMap[x, z] = 0.0f;
            }
        }

        // Set all the height values added to the height map.
        terrainData.SetHeights(0, 0, heightMap);

        return;
    }

    private void OnEnable()
    {
        Debug.Log("Initializing Terrain Data");

        // Get the terrain component.
        terrain = GetComponent<Terrain>();

        // Get the terrain data from the active terrain component. (used for multiple terrains)
        terrainData = Terrain.activeTerrain.terrainData;
    }

    private void Awake()
    {
        // Create a tag manager and add the existing tags to it.
        SerializedObject tagManager = new SerializedObject(AssetDatabase.LoadAllAssetsAtPath("ProjectSettings/TagManager.asset")[0]);

        // Create a tags property which will import all the tags from the tag manager.
        SerializedProperty tagsProperty = tagManager.FindProperty("tags");

        // Add new tags to the tag manager.
        AddTag(tagsProperty, "Terrain");
        AddTag(tagsProperty, "Cloud");
        AddTag(tagsProperty, "Shore");

        // Apply tag changes to tag database.
        tagManager.ApplyModifiedProperties();

        gameObject.tag = "Terrain";

        return;
    }

    void AddTag(SerializedProperty tagsProperty, string newTag)
    {
        // Ensure the tag doesn't already exist.
        for (int currentTag = 0; currentTag < tagsProperty.arraySize; currentTag++)
        {
            SerializedProperty tag = tagsProperty.GetArrayElementAtIndex(currentTag);

            if (tag.stringValue.Equals(newTag))
            {
                return;
            }
        }

        tagsProperty.InsertArrayElementAtIndex(0);
        SerializedProperty newTagProperty = tagsProperty.GetArrayElementAtIndex(0);
        newTagProperty.stringValue = newTag;
    }

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}

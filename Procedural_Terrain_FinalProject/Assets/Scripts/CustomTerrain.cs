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

    // Scaling for the loaded height map.
    public Vector3 heightMapScale = new Vector3(1.0f, 1.0f, 1.0f);

    // Reset terrain before generating new height map.
    public bool resetTerrain = true;

    /*******************
    **  PERLIN NOISE  **
    *******************/
    public float perlinXScale = 0.01f;
    public float perlinYScale = 0.01f;
    public int perlinOffsetX = 0;
    public int perlinOffsetY = 0;
    public int perlinOctaves = 3;
    public float perlinPersistance = 8.0f;
    public float perlinHeightScale = 0.09f;

    /****************************
    **  MULTIPLE PERLIN NOISE  **
    ****************************/
    [System.Serializable]
    public class PerlinParameters
    {
        public float mPerlinXScale = 0.01f;
        public float mPerlinYScale = 0.01f;
        public int mPerlinOffsetX = 0;
        public int mPerlinOffsetY = 0;
        public int mPerlinOctaves = 3;
        public float mPerlinPersistance = 8.0f;
        public float mPerlinHeightScale = 0.09f;
        public bool remove = false;
    }

    public List<PerlinParameters> perlinParameters = new List<PerlinParameters>()
    {
        new PerlinParameters()
    };

    // The terrain object.
    public Terrain terrain;

    // The terrain data object.
    public TerrainData terrainData;

    float[,] GetHeightMap()
    {
        // Reset the height map.
        if (resetTerrain)
        {
            return new float[terrainData.heightmapWidth, terrainData.heightmapHeight];
        }

        // Get the current height map.
        return terrainData.GetHeights(0, 0, terrainData.heightmapWidth, terrainData.heightmapHeight);
    }

    // Simple Perlin Noise Terrain Generation.
    public void SimplePerlin()
    {
        float[,] heightMap = GetHeightMap();

        for (int y = 0; y < terrainData.heightmapHeight; y++)
        {
            for (int x = 0; x < terrainData.heightmapWidth; x++)
            {
                heightMap[x, y] += Mathf.PerlinNoise((x + perlinOffsetX) * perlinXScale, (y + perlinOffsetY) * perlinYScale);
            }
        }

        terrainData.SetHeights(0, 0, heightMap);

        return;
    }

    // Fractal Brownian Motion Perlin Noise Terrain Generation.
    public void FractaBrownianMotionPerlin()
    {
        float[,] heightMap = GetHeightMap();

        for (int y = 0; y < terrainData.heightmapHeight; y++)
        {
            for (int x = 0; x < terrainData.heightmapWidth; x++)
            {
                heightMap[x, y] += Utils.fBM((x + perlinOffsetX) * perlinXScale, (y + perlinOffsetY) * perlinYScale, perlinOctaves, perlinPersistance) * perlinHeightScale;
            }
        }

        terrainData.SetHeights(0, 0, heightMap);

        return;
    }

    // Multiple Perlin Noise Terrain Generation.
    public void MultiplePerlin()
    {
        float[,] heightMap = GetHeightMap();

        for (int y = 0; y < terrainData.heightmapWidth; y++)
        {
            for (int x = 0; x < terrainData.heightmapHeight; x++)
            {
                foreach (PerlinParameters perlinParameter in perlinParameters)
                {
                    heightMap[x, y] += Utils.fBM
                        (
                             (x + perlinParameter.mPerlinOffsetX) * perlinParameter.mPerlinXScale
                            ,(y + perlinParameter.mPerlinOffsetY) * perlinParameter.mPerlinYScale
                            ,perlinParameter.mPerlinOctaves
                            ,perlinParameter.mPerlinPersistance
                        ) * perlinParameter.mPerlinHeightScale;
                }
            }
        }

        terrainData.SetHeights(0, 0, heightMap);
    }

    public void AddNewPerlin()
    {
        perlinParameters.Add(new PerlinParameters());

        return;
    }

    public void RemovePerlin()
    {
        List<PerlinParameters> keptPerlinParameters = new List<PerlinParameters>();

        for (int currentParameter = 0; currentParameter < perlinParameters.Count; currentParameter++)
        {
            if(!perlinParameters[currentParameter].remove)
            {
                keptPerlinParameters.Add(perlinParameters[currentParameter]);
            }
        }

        if (keptPerlinParameters.Count == 0)
        {
            keptPerlinParameters.Add(perlinParameters[0]);
        }

        perlinParameters = keptPerlinParameters;

        return;
    }

    public void Voronoi()
    {
        float[,] heightMap = GetHeightMap();

        float fallOff = 0.5f;

        Vector3 peak = new Vector3(256.0f, 0.2f, 256.0f);
            //new Vector3(UnityEngine.Random.Range(0, terrainData.heightmapWidth),
            //            UnityEngine.Random.Range(0.0f, 1.0f),
            //            UnityEngine.Random.Range(0, terrainData.heightmapHeight)
            //                  );

        heightMap[(int)peak.x, (int)peak.z] = peak.y;

        Vector2 peakLocation = new Vector2(peak.x, peak.z);

        float maxDistance = Vector2.Distance(Vector2.zero, new Vector2(terrainData.heightmapWidth, terrainData.heightmapHeight));

        for (int y = 0; y < terrainData.heightmapHeight; y++)
        {
            for (int x = 0; x < terrainData.heightmapWidth; x++)
            {
                if (!(x == peak.x && y == peak.z))
                {
                    float distanceToPeak = Vector2.Distance(peakLocation, new Vector2(x, y)) * fallOff;
                    heightMap[x, y] = peak.y - distanceToPeak / maxDistance;
                }
            }
        }

        terrainData.SetHeights(0, 0, heightMap);

        return;
    }

    // Generate a random terrain height map.
    public void RandomTerrain()
    {
        // 2D height map array. Get current height map.
        float[,] heightMap = GetHeightMap();

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
        float[,] heightMap = GetHeightMap();

        for (int x = 0; x < terrainData.heightmapWidth; x++)
        {
            for (int z = 0; z < terrainData.heightmapHeight; z++)
            {
                heightMap[x, z] += heightMapImage.GetPixel((int)(x * heightMapScale.x), (int)(z * heightMapScale.z)).grayscale * heightMapScale.y;
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

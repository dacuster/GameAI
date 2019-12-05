using UnityEditor;
using UnityEngine;
using System;
using System.Collections.Generic;
using System.Linq;

// Make sure the script runs in editor mode as well as play mode.
[ExecuteInEditMode]

public class CustomTerrain : MonoBehaviour
{
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

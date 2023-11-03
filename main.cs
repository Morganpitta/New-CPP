using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SpawnZone : MonoBehaviour
{
    public float spacing;
    public Vector3 bottomRightCorner = new Vector3();
    public Vector3 topLeftCorner = new Vector3();

    public GameObject particle;

    private void SummonParticle(Vector3 position , GameObject objectToInstantiate)
    {
        Instantiate(objectToInstantiate, position , Quaternion.identity);
    }

void Start()
{
    // Size of box
    Vector3 scale = transform.lossyScale;
    Vector3 bottomRightCorner = transform.position - (scale / 2);
    Vector3 topLeftCorner = transform.position + (scale / 2);

    int xSteps = (int)(scale.x / spacing);
    int ySteps = (int)(scale.y / spacing);
    int zSteps = (int)(scale.z / spacing);

    for ( float xCoord = bottomRightCorner.x; xCoord <= topLeftCorner.x; xCoord += spacing.x )
    {
        for ( float yCoord = bottomRightCorner.y; yCoord <= topLeftCorner.y; yCoord += spacing.y )
        {
            for ( float zCoord = bottomRightCorner.z; zCoord <= topLeftCorner.z; zCoord += spacing.z )
            {

                SummonParticle( new Vector3(xCoord, yCoord, zCoord) , particle );
                
            }
        }
    }
}

    void Update()
    {

    }
}
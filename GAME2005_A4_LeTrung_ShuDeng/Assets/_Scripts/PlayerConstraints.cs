using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerConstraints : MonoBehaviour
{
    public float XMin, XMax, ZMin, ZMax;
    // Update is called once per frame
    void Update()
    {
        Vector3 position = GetComponent<Transform>().position;
        //if (position.x > 10)
        //{
        //    position.x = 10;
        //}
        //else if (position.x < -10)
        //{
        //    position.x = -10;
        //}
        //if (position.y > 10)
        //{
        //    position.y = 10;
        //}
        //else if (position.y < -10)
        //{
        //    position.y = -10;
        //}
        position.x = Mathf.Max(XMin, Mathf.Min(position.x, XMax));
        position.z = Mathf.Max(ZMin, Mathf.Min(position.z, ZMax));
        GetComponent<Transform>().position = position;
    }
}

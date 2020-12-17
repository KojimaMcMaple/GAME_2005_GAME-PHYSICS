using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerConstraints : MonoBehaviour
{
    public float XMin, XMax, ZMin, ZMax;
    // Update is called once per frame
    void FixedUpdate()
    {
        Vector3 position = transform.position;
        position.x = Mathf.Max(XMin, Mathf.Min(position.x, XMax));
        position.z = Mathf.Max(ZMin, Mathf.Min(position.z, ZMax));
        transform.position = position;
        GetComponent<CharacterController>().center = Vector3.zero;
    }
}

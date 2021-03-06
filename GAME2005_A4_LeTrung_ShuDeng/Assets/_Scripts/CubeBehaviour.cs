﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Color = UnityEngine.Color;


[System.Serializable]
public class CubeBehaviour : MonoBehaviour
{
    public Vector3 size;
    public Vector3 max, min;
    public static float frictionFactor = 0.2f;
    public float cubeMass = 0.1f;
    [HideInInspector]
    public Vector3 velocity, acceleration;
    private Vector3 frictionAcceleration;
    public bool isStatic;
    public bool isColliding;
    public bool debug;
    public List<CubeBehaviour> contacts;

    private MeshFilter meshFilter;
    private Bounds bounds;

    // Start is called before the first frame update
    void Start()
    {
        debug = false;
        meshFilter = GetComponent<MeshFilter>();

        bounds = meshFilter.mesh.bounds;
        size = bounds.size;

        velocity = Vector3.zero;
        acceleration = isStatic? Vector3.zero : new Vector3(0.0f, -10.0f, 0.0f);
    }

    // Update is called once per frame
    void Update()
    {
        max = Vector3.Scale(bounds.max, transform.localScale) + transform.position;
        min = Vector3.Scale(bounds.min, transform.localScale) + transform.position;
    }

    void FixedUpdate()
    {
        // physics related calculations
        if (!isStatic)
        {
            Vector3 pos = transform.position;
            if (Mathf.Abs(pos.y - 0.55f) < 0.001f)
            {
                frictionAcceleration = -velocity.normalized * frictionFactor * 10.0f;
                if (velocity.magnitude - frictionAcceleration.magnitude * Time.deltaTime > 0)
                {
                    velocity += frictionAcceleration * Time.deltaTime;
                }
            }

            velocity += acceleration * Time.deltaTime;

            pos += velocity * Time.deltaTime;
            if (pos.x > 9.5f)
            {
                pos.x = 9.5f;
                velocity.x *= -1;
            }
            else if (pos.x < -9.5f)
            {
                pos.x = -9.5f;
                velocity.x *= -1;
            }
            if (pos.z > 9.5f)
            {
                pos.z = 9.5f;
                velocity.z *= -1;
            }
            else if (pos.z < -9.5f)
            {
                pos.z = -9.5f;
                velocity.z *= -1;
            }
            if (pos.y > 4.5f)
            {
                pos.y = 4.5f;
                velocity.y *= -1;
            }
            else if (pos.y < 0.55f)
            {
                pos.y = 0.55f;
                velocity.y *= -0.5f;
            }
            transform.position = pos;
        }        
    }

    private void OnDrawGizmos()
    {
        if (debug)
        {
            Gizmos.color = Color.magenta;

            Gizmos.DrawWireCube(transform.position, Vector3.Scale(new Vector3(1.0f, 1.0f, 1.0f), transform.localScale));
        }
    }
}

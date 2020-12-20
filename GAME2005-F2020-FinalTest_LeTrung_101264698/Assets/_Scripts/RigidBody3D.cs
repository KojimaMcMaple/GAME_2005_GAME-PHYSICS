using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public enum BodyType
{
    STATIC,
    DYNAMIC
}


[System.Serializable]
public class RigidBody3D : MonoBehaviour
{
    [Header("Gravity Simulation")]
    public float gravityScale;
    public float mass;
    public BodyType bodyType;
    public float timer;
    public bool isFalling;
    public bool isPushed;

    [Header("Attributes")]
    public Vector3 velocity;
    public Vector3 acceleration;
    private float gravity;

    // Start is called before the first frame update
    void Start()
    {
        timer = 0.0f;
        gravity = -0.001f;
        velocity = Vector3.zero;
        acceleration = new Vector3(0.0f, gravity * gravityScale, 0.0f);
        if (bodyType == BodyType.DYNAMIC)
        {
            isFalling = true;
        }
    }

    // Update is called once per frame
    void Update()
    {
        if (bodyType == BodyType.DYNAMIC)
        {
            if (isFalling)
            {
                timer += Time.deltaTime;
                
                if (gravityScale < 0)
                {
                    gravityScale = 0;
                }

                if (gravityScale > 0)
                {
                    acceleration = new Vector3(0.0f, gravity * gravityScale, 0.0f);
                    if (transform.gameObject.CompareTag("Player"))
                    {
                        velocity += new Vector3(0.0f, acceleration.y * 0.5f * timer * timer, 0.0f);
                    }
                    else
                    {
                        velocity += acceleration * 0.5f * timer * timer;
                    }
                    
                }
            }
            else
            {
                acceleration = new Vector3(acceleration.x, 0.0f, acceleration.z);
                velocity += acceleration;
            }
            //if (isPushed)
            //{
            //    acceleration = new Vector3(acceleration.x, 0.0f, acceleration.z);
            //}
            transform.position += velocity;
            
        }
    }

    public void StopXZ()
    {
        acceleration = new Vector3(0.0f,acceleration.y, 0.0f);
        velocity = new Vector3(0.0f,velocity.y, 0.0f);
    }
    public void Stop()
    {
        timer = 0.0f;
        acceleration = new Vector3(0.0f, 0.0f, 0.0f);
        velocity = new Vector3(velocity.x, 0.0f, velocity.z);
        isFalling = false;
    }
}

using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public class CollisionManager : MonoBehaviour
{
    public CubeBehaviour[] cubes;
    public BulletBehaviour[] spheres;

    private static Vector3[] faces;

    // Start is called before the first frame update
    void Start()
    {
        cubes = FindObjectsOfType<CubeBehaviour>();

        faces = new Vector3[]
        {
            Vector3.right,
            Vector3.left,
            Vector3.up,
            Vector3.down,
            Vector3.forward,
            Vector3.back
           

            /*
            (b.max.x - a.min.x),
            (a.max.x - b.min.x),
            (b.max.y - a.min.y),
            (a.max.y - b.min.y),
            (b.max.z - a.min.z),
            (a.max.z - b.min.z)
            */

            /*
             if ((a.min.x <= b.max.x && a.max.x >= b.min.x) &&
            (a.min.y <= b.max.y && a.max.y >= b.min.y) &&
            (a.min.z <= b.max.z && a.max.z >= b.min.z))
             */
        };
    }

    // Update is called once per frame
    void Update()
    {
        spheres = FindObjectsOfType<BulletBehaviour>();

        // check each AABB with every other AABB in the scene
        for (int i = 0; i < cubes.Length; i++)
        {
            for (int j = 0; j < cubes.Length; j++)
            {
                if (i != j)
                {
                    CheckAABBs(cubes[i], cubes[j]);
                }
            }
        }

        // Check each sphere against each AABB in the scene
        foreach (var sphere in spheres)
        {
            foreach (var cube in cubes)
            {
                if (cube.name != "Player")
                {
                    CheckCubeBulletAABB(sphere, cube);
                }
                
            }
        }


    }

    public static void CheckCubeBulletAABB(BulletBehaviour s, CubeBehaviour b)
    {
        if ((s.min.x <= b.max.x && s.max.x >= b.min.x) &&
            (s.min.y <= b.max.y && s.max.y >= b.min.y) &&
            (s.min.z <= b.max.z && s.max.z >= b.min.z))
        {
            // determine the distances between the contact extents
            float[] distances = {
                (b.max.x - s.min.x),
                (s.max.x - b.min.x),
                (b.max.y - s.min.y),
                (s.max.y - b.min.y),
                (b.max.z - s.min.z),
                (s.max.z - b.min.z)
            };

            float penetration = float.MaxValue;
            Vector3 face = Vector3.zero;

            // check each face to see if it is the one that connected
            for (int i = 0; i < 6; i++)
            {
                if (distances[i] < penetration)
                {
                    // determine the penetration distance
                    penetration = distances[i];
                    face = faces[i];
                }
                s.penetration = penetration;
                s.collisionNormal = face*-1.0f;
                //s.isColliding = true;


                Reflect(s);
            }
        }
    }
    
    public static void CheckSphereAABB(BulletBehaviour s, CubeBehaviour b)
    {
        //// get box closest point to sphere center by clamping
        //var x = Mathf.Max(b.min.x, Mathf.Min(s.transform.position.x, b.max.x));
        //var y = Mathf.Max(b.min.y, Mathf.Min(s.transform.position.y, b.max.y));
        //var z = Mathf.Max(b.min.z, Mathf.Min(s.transform.position.z, b.max.z));

        //var distance = Math.Sqrt((x - s.transform.position.x) * (x - s.transform.position.x) +
        //                         (y - s.transform.position.y) * (y - s.transform.position.y) +
        //                         (z - s.transform.position.z) * (z - s.transform.position.z));

        //if ((distance < s.radius) && (!s.isColliding))
        //{
        //    // determine the distances between the contact extents
        //    float[] distances = {
        //        (b.max.x - s.transform.position.x),
        //        (s.transform.position.x - b.min.x),
        //        (b.max.y - s.transform.position.y),
        //        (s.transform.position.y - b.min.y),
        //        (b.max.z - s.transform.position.z),
        //        (s.transform.position.z - b.min.z)
        //    };

        //    float penetration = float.MaxValue;
        //    Vector3 face = Vector3.zero;

        //    // check each face to see if it is the one that connected
        //    for (int i = 0; i < 6; i++)
        //    {
        //        if (distances[i] < penetration)
        //        {
        //            // determine the penetration distance
        //            penetration = distances[i];
        //            face = faces[i];
        //        }
        //    }

        //    s.penetration = penetration;
        //    s.collisionNormal = face;
        //    //s.isColliding = true;

            
        //    Reflect(s);
        //}

    }
    
    // This helper function reflects the bullet when it hits an AABB face
    private static void Reflect(BulletBehaviour s)
    {
        if ((s.collisionNormal == Vector3.forward) || (s.collisionNormal == Vector3.back))
        {
            s.direction = new Vector3(s.direction.x, s.direction.y, -s.direction.z);
        }
        else if ((s.collisionNormal == Vector3.right) || (s.collisionNormal == Vector3.left))
        {
            s.direction = new Vector3(-s.direction.x, s.direction.y, s.direction.z);
        }
        else if ((s.collisionNormal == Vector3.up) || (s.collisionNormal == Vector3.down))
        {
            s.direction = new Vector3(s.direction.x, -s.direction.y, s.direction.z);
        }
    }


    public static void CheckAABBs(CubeBehaviour a, CubeBehaviour b)
    {
        // A CONTROLS B
        
        Contact contactA = new Contact(a);
        Contact contactB = new Contact(b);
        var a_body = a.gameObject.GetComponent<RigidBody3D>();
        var b_body = b.gameObject.GetComponent<RigidBody3D>();

        if ((a.min.x <= b.max.x && a.max.x >= b.min.x) &&
            (a.min.y <= b.max.y && a.max.y >= b.min.y) &&
            (a.min.z <= b.max.z && a.max.z >= b.min.z))
        {
            // determine the distances between the contact extents
            float[] distances = {
                (b.max.x - a.min.x),
                (a.max.x - b.min.x),
                (b.max.y - a.min.y),
                (a.max.y - b.min.y),
                (b.max.z - a.min.z),
                (a.max.z - b.min.z)
            };

            float penetration = float.MaxValue;
            Vector3 face = Vector3.zero;

            // check each face to see if it is the one that connected
            for (int i = 0; i < 6; i++)
            {
                if (distances[i] < penetration)
                {
                    // determine the penetration distance
                    penetration = distances[i];
                    face = faces[i];
                }
            }
            
            // set the contact properties
            contactB.face = face;
            contactA.face = face*-1.0f;
            contactB.penetration = penetration;


            // check if contact does not exist
            if (!a.contacts.Contains(contactB))
            {
                
                
                // remove any contact that matches the name but not other parameters
                for (int i = a.contacts.Count - 1; i > -1; i--)
                {
                    if (a.contacts[i].cube.name.Equals(contactB.cube.name))
                    {
                        a.contacts.RemoveAt(i);
                    }
                }
                
                if (contactA.face == Vector3.down)
                {
                    a.gameObject.transform.position = new Vector3(a.gameObject.transform.position.x, a.gameObject.transform.position.y + contactB.penetration, a.gameObject.transform.position.z);
                    //if (a.gameObject.CompareTag("Player"))
                    //{
                    //    Debug.Log("pos = " + a.gameObject.transform.position.y);
                    //    Debug.Log("pene = " + contactB.penetration);
                    //}
                    a_body.Stop();
                    a.isGrounded = true;
                }

                // add the new contact
                a.contacts.Add(contactB);
                a.isColliding = true;

                // move when pushed

                if (a_body.bodyType == BodyType.DYNAMIC &&
                    b_body.bodyType == BodyType.DYNAMIC)
                {
                    if (!b.gameObject.CompareTag("Player"))
                    {
                        //if ((contactB.face == Vector3.forward))
                        //{
                        //    b.gameObject.transform.position += new Vector3(0.0f, 0.0f, 2.0f);
                        //}
                        //else if ((contactB.face == Vector3.back))
                        //{
                        //    b.gameObject.transform.position += new Vector3(0.0f, 0.0f, -2.0f);
                        //}
                        //else if ((contactB.face == Vector3.right))
                        //{
                        //    b.gameObject.transform.position += new Vector3(2.0f, 0.0f, 0.0f);
                        //}
                        //else if ((contactB.face == Vector3.left))
                        //{
                        //    b.gameObject.transform.position += new Vector3(-2.0f, 0.0f, 0.0f);
                        //}

                        //var a_vel = a.gameObject.GetComponent<RigidBody3D>().velocity;
                        //if ((contactB.face == Vector3.forward))
                        //{
                        //    b.gameObject.transform.position += new Vector3(0.0f, 0.0f, a_vel.z);
                        //}
                        //else if ((contactB.face == Vector3.back))
                        //{
                        //    b.gameObject.transform.position += new Vector3(0.0f, 0.0f, a_vel.z);
                        //}
                        //else if ((contactB.face == Vector3.right))
                        //{
                        //    b.gameObject.transform.position += new Vector3(a_vel.x, 0.0f, 0.0f);
                        //}
                        //else if ((contactB.face == Vector3.left))
                        //{
                        //    b.gameObject.transform.position += new Vector3(a_vel.x, 0.0f, 0.0f);
                        //}
                        
                        if ((contactA.face == Vector3.forward))
                        {
                            b_body.acceleration = new Vector3(0.0f, b_body.acceleration.y, 0.1f);
                        }
                        else if ((contactA.face == Vector3.back))
                        {
                            b_body.acceleration = new Vector3(0.0f, b_body.acceleration.y, -0.1f);
                        }
                        else if ((contactA.face == Vector3.right))
                        {
                            b_body.acceleration = new Vector3(0.1f, b_body.acceleration.y, 0.0f);
                        }
                        else if ((contactA.face == Vector3.left))
                        {
                            b_body.acceleration = new Vector3(-0.1f, b_body.acceleration.y, 0.0f);
                        }


                        //    if ((contactB.face == Vector3.forward && a_vel.z < 0) ||
                        //(contactB.face == Vector3.back && a_vel.z > 0) ||
                        //(contactB.face == Vector3.right && a_vel.x < 0) ||
                        //(contactB.face == Vector3.left && a_vel.x > 0))
                        //    {
                        //        //Debug.Log(b.gameObject.name);
                        //        b_vel = a_vel;
                        //        b.gameObject.transform.position += new Vector3(-b_vel.x,
                        //                                                            0.0f,
                        //                                                            -b_vel.z);
                        //        //Debug.Log(b.gameObject.transform.position.y);
                        //    }


                    }
                }
            }
        }
        else
        {
            if (a.contacts.Exists(x => x.cube.gameObject.name == b.gameObject.name))
            {
                a.isColliding = false;
                
                if (a_body.bodyType == BodyType.DYNAMIC)
                {
                    var prev_b_contact_face = a.contacts.Find(x => x.cube.gameObject.name.Equals(b.gameObject.name)).face;
                    if (
                        prev_b_contact_face == Vector3.forward ||
                        prev_b_contact_face == Vector3.back ||
                        prev_b_contact_face == Vector3.left ||
                        prev_b_contact_face == Vector3.right
                        )
                    {
                        b_body.StopXZ();
                    }
                    if (prev_b_contact_face == Vector3.up)
                    {
                        a_body.isFalling = true;
                        a.isGrounded = false;
                    }
                }
                a.contacts.Remove(a.contacts.Find(x => x.cube.gameObject.name.Equals(b.gameObject.name)));
            }
        }

        //if (a.isColliding && a.gameObject.CompareTag("Player"))
        //{
        //    if (b.gameObject.GetComponent<RigidBody3D>().bodyType == BodyType.DYNAMIC)
        //    {
        //        var a_vel = a.gameObject.GetComponent<RigidBody3D>().velocity;
        //        var b_vel = b.gameObject.GetComponent<RigidBody3D>().velocity;
        //        b_vel = a_vel;
        //        b.gameObject.transform.position += new Vector3(b_vel.x,
        //                                                            0.0f,
        //                                                            b_vel.z);

        //        //if ((contactB.face == Vector3.forward && a_vel.z < 0) ||
        //        //    (contactB.face == Vector3.back && a_vel.z > 0) ||
        //        //    (contactB.face == Vector3.right && a_vel.x < 0) ||
        //        //    (contactB.face == Vector3.left && a_vel.x > 0))
        //        //{
        //        //    //Debug.Log(b.gameObject.name);
        //        //    b_vel = a_vel;
        //        //    b.gameObject.transform.position += new Vector3(b_vel.x,
        //        //                                                        0.0f,
        //        //                                                        b_vel.z);
        //        //    //Debug.Log(b.gameObject.transform.position.y);
        //        //}
        //    }
        //}
            
    }
}

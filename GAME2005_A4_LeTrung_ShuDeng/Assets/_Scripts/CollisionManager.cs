using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public class CollisionManager : MonoBehaviour
{
    public CubeBehaviour[] actors;
    public GameObject bullet_manager_go;

    // Start is called before the first frame update
    void Start()
    {
        actors = FindObjectsOfType<CubeBehaviour>();
    }

    // Update is called once per frame
    void Update()
    {
        if (!bullet_manager_go.GetComponent<BulletManager>().IsActiveListEmpty())
        {
            for (int i = 0; i < bullet_manager_go.GetComponent<BulletManager>().bullet_pool.Count; i++)
            {
                for (int j = 0; j < actors.Length; j++)
                {
                    CheckIntersectSphereAABB(bullet_manager_go.GetComponent<BulletManager>().bullet_pool[i].GetComponent<BulletBehaviour>(), actors[j]);
                }
            }
        }

        for (int i = 0; i < actors.Length; i++)
        {
            for (int j = i + 1; j < actors.Length; j++)
            {
                CheckAABBs(actors[i], actors[j]);
            }
        }
    }

    public static void CheckIntersectSphereAABB(BulletBehaviour sphere, CubeBehaviour box)
    {
        var sphere_x = sphere.transform.position.x;
        var sphere_y = sphere.transform.position.y;
        var sphere_z = sphere.transform.position.z;

        Vector3 normal_reflect_vector = Vector3.zero;

        var x = Mathf.Max(box.min.x, Mathf.Min(sphere_x, box.max.x));
        var y = Mathf.Max(box.min.y, Mathf.Min(sphere_y, box.max.y));
        var z = Mathf.Max(box.min.z, Mathf.Min(sphere_z, box.max.z));

        var distance = Mathf.Sqrt((x - sphere_x) * (x - sphere_x) +
            (y - sphere_y) * (y - sphere_y) +
            (z - sphere_z) * (z - sphere_z)
            );

        if (distance < (sphere.radius))
        {
            if (!sphere.contacts.Contains(box))
            {
                sphere.contacts.Add(box);
                sphere.is_colliding = true;

                if (sphere_x <= box.max.x && sphere_x >= box.min.x)
                {
                    if (sphere_y <= box.max.y && sphere_y >= box.min.y)
                    {
                        if (sphere_z <= box.min.z)// BACK
                        {
                            normal_reflect_vector = Vector3.back;
                            //if(sphere.speed == 5)
                            //{
                            //    Debug.Log(">>> BACK!");
                            //}
                        }
                        else// FRONT
                        {
                            normal_reflect_vector = Vector3.forward;
                            //if (sphere.speed == 5)
                            //{
                            //    Debug.Log(">>> FRONT!");
                            //}
                        }

                    }
                    else
                    {
                        if (sphere_y <= box.min.y)//BOTTOM
                        {
                            normal_reflect_vector = Vector3.down;
                            //if (sphere.speed == 5)
                            //{
                            //    Debug.Log(">>> BOTTOM!");
                            //}
                        }
                        else// TOP
                        {
                            normal_reflect_vector = Vector3.up;
                            //if (sphere.speed == 5)
                            //{
                            //    Debug.Log(">>> TOP!");
                            //}
                        }
                    }
                }
                else
                {
                    if (sphere_x <= box.min.x)//RIGHT
                    {
                        normal_reflect_vector = Vector3.right;
                        //if (sphere.speed == 5)
                        //{
                        //    Debug.Log(">>> RIGHT!");
                        //}
                    }
                    else// LEFT
                    {
                        normal_reflect_vector = Vector3.left;
                        //if (sphere.speed == 5)
                        //{
                        //    Debug.Log(">>> LEFT!");
                        //}
                    }
                }

                //sphere.direction.x = -sphere.direction.x;
                //sphere.direction.y = -sphere.direction.y;
                //sphere.direction.z = -sphere.direction.z;
                sphere.speed -= 2.5f;
                if (sphere.speed == 0.0f)
                {
                    sphere.speed = -0.1f;
                }
                sphere.direction = Vector3.Reflect(sphere.direction, normal_reflect_vector);
            }
        }
        else
        {
            if (sphere.contacts.Contains(box))
            {
                sphere.contacts.Remove(box);
                sphere.is_colliding = false;
            }
            //sphere.direction.x = -sphere.direction.x;
            //sphere.direction.y = -sphere.direction.y;
            //sphere.direction.z = -sphere.direction.z;
            if (box.isStatic)
            {
                sphere.speed -= 1;
                sphere.direction = Vector3.Reflect(sphere.direction, normal_reflect_vector);
            }
            else
            {
                Vector3 sphereSpeedNormalDir = Vector3.Project(sphere.direction * sphere.speed, normal_reflect_vector);
                Vector3 boxSpeedNormalDir = Vector3.Project(box.velocity, normal_reflect_vector);
                Vector3 finalSphereSpeedNormDir = ((sphere.bulletMass - box.cubeMass) * sphereSpeedNormalDir +
                    2 * box.cubeMass * boxSpeedNormalDir) / (sphere.bulletMass + box.cubeMass);
                Vector3 finalBoxSpeedNormDir = ((box.cubeMass - sphere.bulletMass) * boxSpeedNormalDir +
                    2 * sphere.bulletMass * sphereSpeedNormalDir) / (sphere.bulletMass + box.cubeMass);
                for (int i = 0; i < 3; ++i)
                {
                    if (finalSphereSpeedNormDir[i] == 0)
                    {
                        finalSphereSpeedNormDir[i] = (sphere.speed * sphere.direction)[i];
                    }
                    if (finalBoxSpeedNormDir[i] != 0)
                    {
                        box.velocity[i] = finalBoxSpeedNormDir[i];
                    }
                }
                sphere.speed = finalSphereSpeedNormDir.magnitude;
                sphere.direction = finalSphereSpeedNormDir.normalized;
            }
        }
    }

    public static void CheckAABBs(CubeBehaviour a, CubeBehaviour b)
    {
        if ((a.min.x <= b.max.x && a.max.x >= b.min.x) &&
            (a.min.y <= b.max.y && a.max.y >= b.min.y) &&
            (a.min.z <= b.max.z && a.max.z >= b.min.z))
        {
            if (!a.contacts.Contains(b))
            {
                a.contacts.Add(b);
                a.isColliding = true;
            }
            if (!a.isStatic)
            {

            }
        }
        else
        {
            if (a.contacts.Contains(b))
            {
                a.contacts.Remove(b);
                a.isColliding = false;
            }           
        }
    }
}

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
            for (int i = 0; i < bullet_manager_go.GetComponent<BulletManager>().active_bullet_list.Count; i++)
            {
                for (int j = 0; j < actors.Length; j++)
                {
                    CheckIntersectSphereAABB(bullet_manager_go.GetComponent<BulletManager>().active_bullet_list[i].GetComponent<BulletBehaviour>(), actors[j]);
                }
            }
        }

        for (int i = 0; i < actors.Length; i++)
        {
            for (int j = 0; j < actors.Length; j++)
            {
                if (i != j)
                {
                    CheckAABBs(actors[i], actors[j]);
                }
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
            if(sphere_x<= box.max.x && sphere_x >= box.min.x)
            {
                if(sphere_y <= box.max.y && sphere_y >= box.min.y)
                {
                    if(sphere_z<= box.min.z)// BACK
                    {
                        normal_reflect_vector = Vector3.back;
                    }
                    else// FRONT
                    {
                        normal_reflect_vector = Vector3.forward;
                    }
                    
                }
                else
                {
                    if(sphere_y<= box.min.y)//BOTTOM
                    {
                        normal_reflect_vector = Vector3.down;
                    }
                    else// TOP
                    {
                        normal_reflect_vector = Vector3.up;
                    }
                }
            }
            else
            {
                if (sphere_x <= box.min.x)//RIGHT
                {
                    normal_reflect_vector = Vector3.right;
                }
                else
                {
                    normal_reflect_vector = Vector3.left;
                }
            }

            //sphere.direction.x = -sphere.direction.x;
            //sphere.direction.y = -sphere.direction.y;
            //sphere.direction.z = -sphere.direction.z;
            sphere.direction = Vector3.Reflect(sphere.direction, normal_reflect_vector);
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

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public class CollisionManager : MonoBehaviour
{
    public CubeBehaviour[] actors;
    public BulletBehaviour[] bullets;

    // Start is called before the first frame update
    void Start()
    {
        actors = FindObjectsOfType<CubeBehaviour>();
    }

    // Update is called once per frame
    void Update()
    {
        bullets = FindObjectsOfType<BulletBehaviour>();
        for (int i = 0; i < bullets.Length; i++)
        {
            for (int j = 0; j < actors.Length; j++)
            {
                CheckIntersectSphereAABB(bullets[i], actors[j]);
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
        var x = Mathf.Max(box.min.x, Mathf.Min(sphere.transform.position.x, box.max.x));
        var y = Mathf.Max(box.min.y, Mathf.Min(sphere.transform.position.y, box.max.y));
        var z = Mathf.Max(box.min.z, Mathf.Min(sphere.transform.position.z, box.max.z));

        var distance = Mathf.Sqrt((x - sphere.transform.position.x) * (x - sphere.transform.position.x) +
            (y - sphere.transform.position.y) * (y - sphere.transform.position.y) +
            (z - sphere.transform.position.z) * (z - sphere.transform.position.z)
            );

        if (distance < (sphere.radius))
        {
            sphere.speed = 0.0f;
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

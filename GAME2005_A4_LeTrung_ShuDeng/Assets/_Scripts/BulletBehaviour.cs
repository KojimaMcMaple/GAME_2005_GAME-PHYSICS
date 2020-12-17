using System.Collections;
using System.Collections.Generic;
using UnityEngine;

[System.Serializable]
public class BulletBehaviour : MonoBehaviour
{
    public float max_speed = 5;
    public float speed;
    
    public Vector3 direction;
    public float range;
    public List<CubeBehaviour> contacts;

    public Vector3 size;
    public float radius;
    private MeshFilter meshFilter;
    private Bounds bounds;
   

    // Start is called before the first frame update
    void Start()
    {
        meshFilter = GetComponent<MeshFilter>();

        bounds = meshFilter.mesh.bounds;
        size = bounds.size;
        //radius = GetComponent<MeshRenderer>().bounds.extents.magnitude;        
        radius = transform.localScale.x/2;
    }

    // Update is called once per frame
    void Update()
    {
        //_Move();
        //_CheckBounds();
    }

    //private void _Move()
    //{
    //    transform.position += direction * speed * Time.deltaTime;
    //}

    //private void _CheckBounds()
    //{
    //    if (Vector3.Distance(transform.position, Vector3.zero) > range)
    //    {
    //        Destroy(gameObject);
    //    }
    //}
}

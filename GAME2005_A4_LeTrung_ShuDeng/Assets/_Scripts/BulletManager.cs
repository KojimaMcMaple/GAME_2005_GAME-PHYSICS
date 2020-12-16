using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BulletManager : MonoBehaviour
{

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        for (int i = 0; i < this.gameObject.transform.childCount; i++)
        {
            var bullet = this.gameObject.transform.GetChild(i);

            //Debug.Log(bullet.position.x);
        }
    }
}


using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BulletManager : MonoBehaviour
{
    public GameObject bullet_go; //input from Editor
    public int pool_size = 10;
    public List<GameObject> bullet_pool;

    // Start is called before the first frame update
    void Start()
    {
        bullet_pool = new List<GameObject>();
        GameObject temp;

        for (int i = 0; i < pool_size; i++)
        {
            temp = Instantiate(bullet_go);
            temp.GetComponent<BulletBehaviour>().bullet_id = i;
            temp.SetActive(false);
            bullet_pool.Add(temp);
        }
    }

    public bool IsActiveListEmpty()
    {
        return ((bullet_pool.Count == 0) ? true : false);
    }

    public GameObject GetPooledBullet()
    {
        for (int i = 0; i < pool_size; i++)
        {
            if (!bullet_pool[i].activeInHierarchy)
            {
                Debug.Log(">>>Spawned: " + bullet_pool[i].GetComponent<BulletBehaviour>().bullet_id);
                return bullet_pool[i];
            }
        }
        return null;
    }

    public void SpawnBullet(Vector3 position, Quaternion rotation, Vector3 direction)
    {
        if (bullet_pool.Count!=0)
        {
            GameObject temp;
            temp = GetPooledBullet();
            if(temp!= null)
            {
                temp.transform.position = position;
                temp.transform.rotation = rotation;
                temp.GetComponent<BulletBehaviour>().direction = direction;
                temp.GetComponent<BulletBehaviour>().speed = temp.GetComponent<BulletBehaviour>().max_speed;
                temp.SetActive(true);
            }
        }
    }

    void DespawnBullet(int active_idx)
    {
        if (!IsActiveListEmpty())
        {
            GameObject temp;
            temp = bullet_pool[active_idx];
            temp.SetActive(false);
        }
        //for (int i = safePendingList.Count - 1; i >= 0; i--) //https://stackoverflow.com/questions/1582285/how-to-remove-elements-from-a-generic-list-while-iterating-over-it
        //{
        //    // some code
        //    // safePendingList.RemoveAt(i);
        //}
    }

    private void _Move()
    {
        if (!IsActiveListEmpty())
        {
            for (int i = 0; i < bullet_pool.Count; i++)
            {
                if (bullet_pool[i].activeSelf)
                {
                    BulletBehaviour bullet = bullet_pool[i].GetComponent<BulletBehaviour>();
                    bullet.transform.position += bullet.direction * bullet.speed * Time.deltaTime;
                }
                
            }
        }
    }

    private void _CheckRest()
    {
        if (!IsActiveListEmpty())
        {
            //for (int i = active_bullet_list.Count - 1; i >= 0; i--) //https://stackoverflow.com/questions/1582285/how-to-remove-elements-from-a-generic-list-while-iterating-over-it
            for (int i = 0; i < bullet_pool.Count; i++)
            {
                BulletBehaviour bullet = bullet_pool[i].GetComponent<BulletBehaviour>();
                if (bullet.speed < 0 && bullet_pool[i].activeSelf == true)
                {
                    bullet.speed = 0.0f;
                    bullet_pool[i].SetActive(false);
                    Debug.Log(">>>DESPAWNED: " + bullet.bullet_id);
                }
            }
        }
    }

    private void _CheckBounds()
    {
        if (!IsActiveListEmpty())
        {
            for (int i = 0; i < bullet_pool.Count; i++)
            {
                BulletBehaviour bullet = bullet_pool[i].GetComponent<BulletBehaviour>();
                if (Vector3.Distance(bullet.transform.position, Vector3.zero) > bullet.range)
                {
                    bullet_pool[i].SetActive(false);
                }
            }
        }
    }

    // Update is called once per frame
    void Update()
    {
        _Move();
        _CheckRest();
        _CheckBounds();
        //for (int i = 0; i < this.gameObject.transform.childCount; i++)
        //{
        //    var bullet = this.gameObject.transform.GetChild(i);

        //    //Debug.Log(bullet.position.x);
        //}
    }
}


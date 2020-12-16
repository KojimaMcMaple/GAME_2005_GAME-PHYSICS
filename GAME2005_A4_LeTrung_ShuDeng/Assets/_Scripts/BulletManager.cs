using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BulletManager : MonoBehaviour
{
    public GameObject bullet_go; //input from Editor
    public int pool_size = 10;
    public List<GameObject> active_bullet_list;
    private List<GameObject> inactive_bullet_list;

    // Start is called before the first frame update
    void Start()
    {
        active_bullet_list = new List<GameObject>();
        inactive_bullet_list = new List<GameObject>();
        GameObject temp;

        for (int i = 0; i < pool_size; i++)
        {
            temp = Instantiate(bullet_go);
            temp.SetActive(false);
            inactive_bullet_list.Add(temp);
        }
    }

    public bool IsActiveListEmpty()
    {
        return ((active_bullet_list.Count == 0) ? true : false);
    }

    public void SpawnBullet(Vector3 position, Quaternion rotation, Vector3 direction)
    {
        if (inactive_bullet_list.Count!=0)
        {
            GameObject temp;
            int last_idx = inactive_bullet_list.Count - 1;
            temp = inactive_bullet_list[last_idx];
            temp.SetActive(true);
            temp.transform.position = position;
            temp.transform.rotation = rotation;
            temp.GetComponent<BulletBehaviour>().direction = direction;
            inactive_bullet_list.RemoveAt(last_idx);
            active_bullet_list.Add(temp);
        }
    }

    void DespawnBullet(int active_idx)
    {
        if (!IsActiveListEmpty())
        {
            GameObject temp;
            temp = active_bullet_list[active_idx];
            temp.SetActive(false);
            active_bullet_list.RemoveAt(active_idx); //erase the i-th element
            inactive_bullet_list.Add(temp);
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
            for (int i = 0; i < active_bullet_list.Count; i++)
            {
                BulletBehaviour temp = active_bullet_list[i].GetComponent<BulletBehaviour>();
                temp.transform.position += temp.direction * temp.speed * Time.deltaTime;
            }
        }
    }

    private void _CheckBounds()
    {
        if (!IsActiveListEmpty())
        {
            for (int i = active_bullet_list.Count - 1; i >= 0; i--) //https://stackoverflow.com/questions/1582285/how-to-remove-elements-from-a-generic-list-while-iterating-over-it
            {
                if (Vector3.Distance(transform.position, Vector3.zero) > active_bullet_list[i].GetComponent<BulletBehaviour>().range)
                {
                    DespawnBullet(i);
                }
            }
        }
    }

    // Update is called once per frame
    void Update()
    {
        _Move();
        _CheckBounds();
        //for (int i = 0; i < this.gameObject.transform.childCount; i++)
        //{
        //    var bullet = this.gameObject.transform.GetChild(i);

        //    //Debug.Log(bullet.position.x);
        //}
    }
}


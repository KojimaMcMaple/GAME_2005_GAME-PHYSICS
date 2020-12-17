using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerBehaviour : MonoBehaviour
{
    public Transform bulletSpawn;
    public GameObject bullet;
    public int fireRate;


    public GameObject bullet_manager_go;

    void start()
    {
    }

    // Update is called once per frame
    void Update()
    {
        _Fire();
    }

    private void _Fire()
    {
        if (Input.GetAxisRaw("Fire1") > 0.0f)
        {
            // delays firing
            if (Time.frameCount % fireRate == 0)
            {
                //var tempBullet = Instantiate(bullet, bulletSpawn.position, Quaternion.identity);
                //tempBullet.GetComponent<BulletBehaviour>().direction = bulletSpawn.forward;

                //tempBullet.transform.SetParent(bulletManager.gameObject.transform);

                bullet_manager_go.GetComponent<BulletManager>().SpawnBullet(bulletSpawn.position, Quaternion.identity, bulletSpawn.forward);
            }

        }
    }
}

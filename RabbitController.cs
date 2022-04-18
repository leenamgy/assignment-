using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RabbitController : MonoBehaviour
{
    [Range(0.1f, 10)]
    public float rabbitSpeed = 1.5f;

    void Start()
    {

    }

    void Update()
    {
        float rotVal = Input.GetAxis("Horizontal");
        float velVal = Input.GetAxis("Vertical");

        transform.Translate(Vector3.forward * velVal * Time.deltaTime * rabbitSpeed);
        transform.Rotate(Vector3.up * rotVal * Time.deltaTime * 150f);
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.tag.Equals("Carrot"))
        {
            Destroy(other.gameObject);
            GameObject effectClone = Instantiate(SceneManager.Inst.carrotEffect, other.transform.position + Vector3.up * 0.4f, Quaternion.identity);
            Destroy(effectClone, 2f);
            SceneManager.Inst.StartEffectSound();
        }
    }

    private void OnTriggerStay(Collider other)
    {
        if (other.tag.Equals("FlowerSpot"))
        {
            rabbitSpeed = 0.6f;
        }
    }

    private void OnTriggerExit(Collider other)
    {
        if (other.tag.Equals("FlowerSpot"))
        {
            rabbitSpeed = 1.5f;
        }
    }
}

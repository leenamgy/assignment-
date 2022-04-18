using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraController : MonoBehaviour
{
    private Camera cam;
    private GameObject rabbit;
    private Vector3 camLocalPosition;

    void Start()
    {
        rabbit = GameObject.Find("Rabbit");
        camLocalPosition = -rabbit.transform.forward * 2.5f + rabbit.transform.up * 1.5f;
        cam = Camera.main;
        cam.transform.position = rabbit.transform.position + camLocalPosition;
        cam.transform.rotation = Quaternion.Euler(18f, 0, 0);
    }

    void Update()
    {

    }

    private void LateUpdate()
    {
        Vector3 camTempPos = rabbit.transform.position - rabbit.transform.forward * 2.5f + rabbit.transform.up * 1.5f;
        cam.transform.rotation = Quaternion.Lerp(cam.transform.rotation, Quaternion.LookRotation(-cam.transform.position + rabbit.transform.position), 0.1f);
        cam.transform.position = Vector3.Lerp(cam.transform.position, camTempPos, 0.1f);
    }
}

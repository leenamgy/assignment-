using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SceneManager : MonoBehaviour
{
    public static SceneManager Inst { get; private set; }
    [Header("MAP INFO")]
    public int carrotCount = 1;

    [Header("PREFABS")]
    public GameObject carrotPrefab;
    public GameObject carrotEffect;

    [Header("MAP INFO")]
    public AudioSource effecSoundBox;

    private void Awake()
    {
        if (Inst == null)
            Inst = this;
    }

    void Start()
    {
        OnStartScene();
    }

    public void StartEffectSound()
    {
        effecSoundBox.Play();
    }

    private void OnStartScene()
    {
        for (int i = 0; i < carrotCount; i++)
        {
            Vector3 randPos = new Vector3(Random.Range(-5, 5f), 0, Random.Range(-5, 5f));
            GameObject carrotClone = Instantiate(carrotPrefab, randPos, Quaternion.identity);
        }
    }
}

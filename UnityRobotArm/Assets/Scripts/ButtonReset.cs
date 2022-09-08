using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using Button = UnityEngine.UI.Button;

public class ButtonReset : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
       GetComponent<Button>().onClick.AddListener(ResetRotation);
    }

    void ResetRotation()
    {
        Transform panel = GameObject.Find("Canvas/JPanel").transform;
        foreach (Transform child in panel)
        {
            child.gameObject.GetComponent<Slider>().value = 0;
        }
    }
    // Update is called once per frame
    void Update()
    {
        
    }
}

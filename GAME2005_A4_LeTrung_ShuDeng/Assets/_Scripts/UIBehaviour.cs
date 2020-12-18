using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UIBehaviour : MonoBehaviour
{
    private InputField[] inputFields;
    public CubeBehaviour cube1, cube2;
    // Start is called before the first frame update
    void Start()
    {
        inputFields = GetComponentsInChildren<InputField>();
    }

    // Update is called once per frame
    void Update()
    {
        if (inputFields[0].text != "")
        {
            cube1.cubeMass = float.Parse(inputFields[0].text);
        }
        else
        {
            inputFields[0].text = cube1.cubeMass.ToString();
        }
        if (inputFields[1].text != "")
        {
            cube2.cubeMass = float.Parse(inputFields[1].text);
        }
        else
        {
            inputFields[1].text = cube2.cubeMass.ToString();
        }
        if (inputFields[2].text != "")
        {
            CubeBehaviour.frictionFactor = float.Parse(inputFields[2].text);
        }
        else
        {
            inputFields[2].text = CubeBehaviour.frictionFactor.ToString();
        }
    }
}

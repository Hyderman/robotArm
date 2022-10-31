using TMPro;
using UnityEngine;
using UnityEngine.UI;

namespace SliderScripts {
    public class SliderScriptJ3 : MonoBehaviour {
        private Slider _slider;
        private TextMeshProUGUI _sliderText;
        private Transform _mesh;
        private Vector3 _currentEulerAngles;

        // Start is called before the first frame update
        void Start() {
            _slider = GetComponent<Slider>();
            _sliderText = transform.GetChild(4).GetComponent<TextMeshProUGUI>();
            _sliderText.text = _slider.value.ToString("0.0");
            _slider.onValueChanged.AddListener((v) => {
                _sliderText.text = v.ToString("0.0");
                _currentEulerAngles = new Vector3(v, 0, 0);
                _mesh = GameObject.Find("robotArm/Base/J1/J2/J3").transform;
                _mesh.localEulerAngles = _currentEulerAngles;
            });
        }

        // Update is called once per frame
        void Update() {

        }
    }
}

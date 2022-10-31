using UnityEngine;

public class MouvementsCamera : MonoBehaviour {
    [SerializeField]
    private float mouseSensitivity = 3.0f;

    [SerializeField]
    private KeyCode focus = KeyCode.F;

    [SerializeField]
    private KeyCode rotationKey = KeyCode.Mouse1;

    [SerializeField]
    private float zoomSpeed = 5f;

    private GameObject _target;
    private Vector3 _targetCenter;

    private Camera _mainCamera;

    void Start() {
        _mainCamera = Camera.main;
    }

    // Update is called once per frame
    void Update() {
        float mouseMoveX = Input.GetAxis("Mouse X");
        float mouseMoveY = Input.GetAxis("Mouse Y");
        if (Input.GetKeyDown(focus))
            FocusTarget();
        float mouseScroll = Input.GetAxis("Mouse ScrollWheel");
        transform.Translate(Vector3.forward * (mouseScroll * zoomSpeed));

        if (Input.GetKey(rotationKey)) {
            transform.RotateAround(_targetCenter, transform.right, mouseMoveY * -mouseSensitivity);
            transform.RotateAround(_targetCenter, Vector3.up, mouseMoveX * mouseSensitivity);
        }
    }

    private void FocusTarget() {
        Ray ray = _mainCamera.ScreenPointToRay(Input.mousePosition);
        RaycastHit hit;
        if (Physics.Raycast(ray, out hit)) {
            _target = hit.collider.gameObject;
            _targetCenter = _target.GetComponent<Renderer>().bounds.center;
            transform.LookAt(_targetCenter);
        }
    }
}

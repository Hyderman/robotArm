using UnityEngine;


public class SceneLikeCamera : MonoBehaviour
{
    [Header("Focus Object")]
    [SerializeField, Tooltip ("Enable double-click to focus on objects?")] 
    private bool doFocus = false;
    [SerializeField] private float focusLimit = 100f;
    [SerializeField] private float minFocusDistance = 5.0f;
    private float _doubleClickTime = .15f;
    private float _cooldown = 0;
    [Header("Undo - Only undoes the Focus Object - The keys must be pressed in order.")]
    [SerializeField] private KeyCode firstUndoKey = KeyCode.LeftControl;
    [SerializeField] private KeyCode secondUndoKey = KeyCode.Z;

    [Header("Movement")]
    [SerializeField] private float moveSpeed = 0.1f;
    [SerializeField] private float rotationSpeed = 2f;
    [SerializeField] private float zoomSpeed = 5f;

    //Cache last pos and rot be able to undo last focus object action.
    private Quaternion _prevRot = new Quaternion();
    private Vector3 _prevPos = new Vector3();

    [Header("Axes Names")]
    [SerializeField, Tooltip("Otherwise known as the vertical axis")] private string mouseY = "Mouse Y";
    [SerializeField, Tooltip("AKA horizontal axis")] private string mouseX = "Mouse X";
    [SerializeField, Tooltip("The axis you want to use for zoom.")] private string zoomAxis = "Mouse ScrollWheel";

    [Header("Anchored Movement"), Tooltip("By default in scene-view, this is done by right-clicking for rotation or middle mouse clicking for up and down")]
    [SerializeField] private KeyCode anchoredMoveKey = KeyCode.Mouse2;

    [SerializeField] private KeyCode anchoredRotateKey = KeyCode.Mouse1;

    private void Start()
    {
        SavePosAndRot();
    }

    void Update()
    {
        if (!doFocus)
            return;

        //Double click for focus 
        if (_cooldown > 0 && Input.GetKeyDown(KeyCode.Mouse0))
            FocusObject();
        if (Input.GetKeyDown(KeyCode.Mouse0))
            _cooldown = _doubleClickTime;

        //--------UNDO FOCUS---------
        if (Input.GetKey(firstUndoKey)) 
        {
            if (Input.GetKeyDown(secondUndoKey))
                GoBackToLastPosition();
        }

        _cooldown -= Time.deltaTime;
    }

    private void LateUpdate()
    {
        Vector3 move = Vector3.zero;

        float mouseMoveY = Input.GetAxis(mouseY);
        float mouseMoveX = Input.GetAxis(mouseX);

        //Move the camera when anchored
        if (Input.GetKey(anchoredMoveKey)) 
        {
            move += Vector3.up * (mouseMoveY * - moveSpeed);
            move += Vector3.right * (mouseMoveX * - moveSpeed);
        }

        //Rotate the camera when anchored
        if (Input.GetKey(anchoredRotateKey)) 
        {
            var transform1 = transform;
            transform.RotateAround(transform1.position, transform1.right, mouseMoveY * -rotationSpeed);
            transform.RotateAround(transform.position, Vector3.up, mouseMoveX * rotationSpeed);
        }

        transform.Translate(move);
        
        //Scroll to zoom
        float mouseScroll = Input.GetAxis(zoomAxis);
        transform.Translate(Vector3.forward * (mouseScroll * zoomSpeed));
    }

    private void FocusObject()
    {
        //To be able to undo
        SavePosAndRot();

        //If we double-clicked an object in the scene, go to its position
        Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
        RaycastHit hit;

        if (Physics.Raycast(ray, out hit, focusLimit))
        {
            GameObject target = hit.collider.gameObject;
            Vector3 targetPos = target.transform.position;
            Vector3 targetSize = hit.collider.bounds.size;

            transform.position = targetPos + GetOffset(targetPos, targetSize);

            transform.LookAt(target.transform);
        }
    }

    private void SavePosAndRot() 
    {
        _prevRot = transform.rotation;
        _prevPos = transform.position;
    }

    private void GoBackToLastPosition() 
    {
        transform.position = _prevPos;
        transform.rotation = _prevRot;
    }

    private Vector3 GetOffset(Vector3 targetPos, Vector3 targetSize)
    {
        Vector3 dirToTarget = targetPos - transform.position;
        float focusDistance = Mathf.Max(targetSize.x, targetSize.z);
        focusDistance = Mathf.Clamp(focusDistance, minFocusDistance, focusDistance);
        return -dirToTarget.normalized * focusDistance;
    }
}
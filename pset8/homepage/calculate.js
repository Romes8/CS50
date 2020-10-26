function calculate()
{
    let first = document.querySelector('#first').value;
    let second = document.querySelector('#second').value;
    let boots = document.querySelector('#boots');
    let boot = document.querySelector('#boot');




    if (first === '' || second === '')
    {
        alert('Bad input');
    }
    else
    {
        let result = first * second;
        if (result == 8)
        {

            document.querySelector('#result').innerHTML = 'Result is: ' + first * second;
            boots.style.visibility = 'visible';
            boot.style.visibility = 'hidden';
        }

        else
        {
            boots.style.visibility = 'hidden';
            boot.style.visibility = 'visible';
        }
    }
}